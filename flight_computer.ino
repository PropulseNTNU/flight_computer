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
 
/*
    Setup of adresses
 */
const uint8_t SD_CS_pin = BUILTIN_SDCARD;
#define LED_pin 13

/*
    Specify the start and end state here, modify the START_STATE
    to the state function you would like to test.
*/
#define START_STATE BURNOUT
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
const String dataFileName = "DataFile.txt";
const String airbrakesFileName = "AbFile.txt";
unsigned long logEveryKMsec = 10;
unsigned long prevLogTime; 

//Init data array
double data[NUM_TYPES];

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
    Serial.println("initialization failed!");
    delay(1000);
  }
  else {
    delay(1000);
    if(init_SD(DATA_FILE, dataFileName.c_str()) && init_SD(AIRBRAKES_FILE, airbrakesFileName.c_str())){
      Serial.println("Successfully opened file(s) on SD card");
    }
    else{
      Serial.println("Successfully opened file on SD card");
    }
    
    delay(2000); 
  }

  //Calibrate BME pressure sensor to read 0m altitude at current location
  calibrateAGL();

  //Setup ARM button pin
  pinMode(ARM_BUTTON_PIN, INPUT);

  //Delete file?
  Serial.println("Commands: \n 'd': delete data log \n 'a': delete airbrakes log \n 'b': delete both logs \n 'k': to contineue ");

  const unsigned long startedWaiting = millis();
  const unsigned long waitNMillis = 10000;

  //Option to remove file using serial for waitNMillis milliseconds
  while(millis() - startedWaiting <= waitNMillis){
    String answer;
    //since serial read only reads one byte at a time we can't use codes longer than one letter
    //look into using readline in the future.
    answer = Serial.read(); 
    if (answer == "d"){
      SD.remove(dataFileName.c_str());
      delay(10);
      init_SD(DATA_FILE, dataFileName.c_str());
      Serial.print("Deleted data file.");
      break;
    }
    else if (answer == "a") {
      SD.remove(airbrakesFileName.c_str());
      delay(10);
      init_SD(AIRBRAKES_FILE, airbrakesFileName.c_str());
      Serial.print("Deleted airbrakes file.");
      break;
    }
    else if (answer == "b") {
      SD.remove(dataFileName.c_str());
      delay(10);
      init_SD(DATA_FILE, dataFileName.c_str());
      delay(10);
      SD.remove(airbrakesFileName.c_str());
      delay(10);
      init_SD(AIRBRAKES_FILE, airbrakesFileName.c_str());
      Serial.print("Deleted both files.");
      break;
    }
    else if (answer == "k") {
      break;
    }
  }
  Serial.println("Continuing..");

  //Setup done -> lights diode on teensy
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, HIGH);

  // initi servos
  init_servo(AIRBRAKES_SERVO, AIRBRAKES_SERVO_PIN);

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
}
