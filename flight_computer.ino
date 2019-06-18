#include <Wire.h>
#include "src/FSM/states.h"
#include "src/FSM/transitions.h"
#include "src/SD_interface/SD_interface.h"
#include "src/servo_interface/servo_interface.h"
#include "src/sensor_interface/sensor_interface.h"
#include "src/xbee_transmitter/xbee_tx.h"

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

//Init xbee
XBee xbee((void*) data, NUM_TYPES * sizeof(data[0]));

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

  //Setup ARM button pin
  pinMode(ARM_BUTTON_PIN, INPUT);

  //Setup done -> lights diode on teensy
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, HIGH);

  // Initialise servos
  init_servo(AIRBRAKES_SERVO, AIRBRAKES_SERVO_PIN, 800, 2200);
  init_servo(DROGUE_SERVO, DROGUE_SERVO_PIN, 800, 2200 );
  init_servo(MAIN_SERVO, MAIN_SERVO_PIN, 600, 2400);

  // Initialise and hold drogue and main chute positions throughout launch
  get_servo(DROGUE_SERVO)->write(DROGUE_RESET_ANGLE);
  get_servo(MAIN_SERVO)->write(MAIN_RESET_ANGLE);
}

void loop()
{ 
  readSensors(data);
  
  //Running the state machine
  state_function = state_funcs[current_state];
  ret_code = return_code(state_function(data));
  current_state = lookup_transition(current_state, ret_code);
  data[STATE] = current_state;

  //Reset IMU when transitioning to ARMED state
  if(ret_code == NEXT && current_state==ARMED){
    get_IMU()->begin();
    delay(100);
  }
  
  //Starting writing to SD card when ARMED 
  if ((current_state >= ARMED) && (millis() - prevLogTime >= logEveryKMsec)) {
      prevLogTime = millis();
      write_SD(DATA_FILE, data, NUM_TYPES);
  }

  Serial.print("Current state: ");
  Serial.println(data[STATE]);
  /*Serial.print("Current gps altitude: ");
  Serial.println(data[ALTITUDE_GPS]);
  Serial.print("Current barometer altitude: ");
  Serial.println(data[ALTITUDE]);
  */
  xbee.transmit();
}
