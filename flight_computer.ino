/*
  This arduino program is currently doing the following:
    1. Initializing sensor objects and log file.
    2. Setting up serial and i2c communication with sensors and SD card.
    3. Setting up the BME280 altitude sensor.
    4. Setting up the BNO055 IMU sensor.
    5. Reading and logging the sensor data to the text file on the SD Card.
    6. Running the Finite State Machine.
*/

#include <Wire.h>
#include "src/FSM/states.h"
#include "src/FSM/transitions.h"
#include "src/SD_interface/SD_interface.h"
#include "src/servo_interface/servo_interface.h"
#include "src/sensor_interface/sensor_interface.h"
#include "src/xbee_transmitter/xbee_tx.h"
#include "src/serial_interface/serial_reader.h"
#include "src/bluetooth/bluetooth.h"



/*
    Setup of adresses
 */
const uint8_t SD_CS_pin = BUILTIN_SDCARD;
#define LED_pin 13

/*
    Specify the start and end state here, modify the START_STATE
    to the state function you would like to test.
*/
#define START_STATE IDLE
#define END_STATE LANDED

/*
    Initialization of the state machine, including legal state function.
*/
int(*state_function)(double[]);

state_func state_funcs[NUM_STATES] = 
    { idle_state, armed_state, burnout_state, 
      airbrakes_state, apogee_state, drogue_state,
      chute_state, landed_state}; 

state current_state = START_STATE;
return_code ret_code = REPEAT;

/*
    Initialization of the data file names.
    IMPORTANT!!!: If the names are too long you will fail to write to the file.......(use short file names)
 */
String dataFileName = "Data.txt";
String airbrakesFileName = "Ab.txt";
String recoveryFileName = "Rec.txt";

unsigned long logEveryKMsec = 10;
unsigned long prevLogTime; 


//Init data array
double data[NUM_TYPES];

//Init bluetooth data array
const int NUM_SENSORS = NUMBER_OF_SENSORS;
double payloadData[NUM_SENSORS]; 


//Init xbee
XBee xbee((void*) data, NUM_TYPES * sizeof(data[0]), (void*) payloadData, NUM_SENSORS * sizeof(data[0]));


void setup()
{
  
  //Setup serial connection
  Serial.begin(9600);
 
  //Start I2C
  Wire.begin();

  delay(500);
  
  Serial.println("Starting I2C communication with BME280");
  if (!get_BME()->beginI2C())
  {
    Serial.println("The BME sensor did not respond. Please check wiring.");
  }
  else {
    Serial.println("BME sensor successfully initialized");
  }
  delay(200);
  
  Serial.println("Setting up the IMU..");
  if (!get_IMU()->begin())
  {
    Serial.println("The IMU sensor did not respond. Please check wiring.");
  }
  else {
    Serial.println("IMU sensor successfully initialized");
  }
  delay(200);
  
  //Setup SD-card module
  if (!SD.begin(SD_CS_pin)) {
    Serial.println("SD initialization failed!");
  }
  else {
      uint8_t fileNumber = 0;
      while (SD.exists(recoveryFileName.c_str()) &&
             SD.exists(airbrakesFileName.c_str()) &&
             SD.exists(dataFileName.c_str())){
            dataFileName = "Data"+ String(fileNumber) + ".txt";
            recoveryFileName = "Rec"+ String(fileNumber) + ".txt";
            airbrakesFileName = "Ab"+ String(fileNumber) + ".txt";
            fileNumber += 1;
      }
      
      if(init_SD(DATA_FILE, dataFileName.c_str()) &&
         init_SD(AIRBRAKES_FILE, airbrakesFileName.c_str()) && 
         init_SD(RECOVERY_FILE, recoveryFileName.c_str())) 
        {
          Serial.println("Successfully opened file(s) on SD card");
        }
      else{
          Serial.println("Failed to opened file(s) on SD card");
      }
  }
  delay(1000);

  //Calibrate BME pressure sensor to read 0m altitude at current location
  calibrateAGL();


  //
  Serial.println("Setup for recieving bluetooth communication");
  if (setupBle(payloadData, NUM_SENSORS))
  {
    Serial.println("Bluetooth setup done");
  }
  else {
    Serial.println("Bluetooth crashed");
  } 

  //Setup ARM button pin
  pinMode(ARM_BUTTON_PIN, INPUT);

  //Setup done -> lights diode on teensy
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, HIGH);

  // Initialise servos
  init_servo(AIRBRAKES_SERVO, AIRBRAKES_SERVO_PIN, 800, 2200);
  init_servo(DROGUE_SERVO, DROGUE_SERVO_PIN, 800, 2200 );
  init_servo(MAIN_SERVO, MAIN_SERVO_PIN, 800, 2200);

  // Initialise and hold drogue and main chute positions throughout launch
  get_servo(DROGUE_SERVO)->write(DROGUE_RESET_ANGLE);
  get_servo(MAIN_SERVO)->write(MAIN_RESET_ANGLE);


}

void loop()
{ 
  readSensors(data);
  //updateSensorData(data);
  
  //bluetooth
  updateDataFromBle(payloadData);
  //for testing bluetooth data
  Serial.println("Data recieved:");
  for(int i= 0; i < NUM_SENSORS; i++){
    Serial.println(payloadData[i]);
  }
  Serial.println("Data end recieved:");
  //test end
  
  
  //Running the state machine
  state_function = state_funcs[current_state];
  
  ret_code = return_code(state_function(data));
  current_state = lookup_transition(current_state, ret_code);
  data[STATE] = current_state;


  //Reset IMU when transitioning to ARMED state
  if(ret_code == NEXT && current_state==ARMED){
    get_IMU()->begin();
  }

  //Starting writing to SD card when ARMED 
  if ((current_state >= ARMED) && (millis() - prevLogTime >= logEveryKMsec)) {
      prevLogTime = millis();
      write_SD(DATA_FILE, data, NUM_TYPES);
  }

  /* Printing for Penumbra */
  Serial.print("state");
  Serial.println(data[STATE]);
  Serial.print("t_h");
  Serial.println(data[1],3);
  Serial.print("t_a");
  Serial.println(data[2],3);

  if(current_state != AIRBRAKES) {
    	Serial.print("est_h");
	    Serial.println(0);
      Serial.print("est_v");
	    Serial.println(0);
      Serial.print("c_s");
		  Serial.println(0);
  }
  
  Serial.print("Current state: ");
  Serial.println(data[STATE]);
  Serial.print("Current gps altitude: ");
  Serial.println(data[ALTITUDE_GPS]);
  Serial.print("Current barometer altitude: ");
  Serial.println(data[ALTITUDE]);
  xbee.transmit();  
}
