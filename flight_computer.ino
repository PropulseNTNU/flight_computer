/*
  This arduino program is currently doing the following:
    1. Initializing sensor objects and log file.
    2. Setting up serial and i2c communication with sensors and SD card.
    3. Setting up the BME280 altitude sensor.
    4. Setting up the BNO055 IMU sensor.
    5. Logging the sensor data to the text file on the SD Card.
    6. Running the Finite State Machine.
*/

#include <Wire.h>
//#include <SPI.h>
#include <Time.h>
#include <SD.h>
#include "src/LED/LED.h"
#include "src/BME280/SparkFunBME280.h"
#include "src/Adafruit_BNO055/Adafruit_BNO055.h"
#include "src/FSM/states.h"
#include "src/FSM/transitions.h"

//Adresses
const int IMU_ADDRESS = 0x28;

/*
    Specify the start and end state here, modify the START_STATE
    to the state function you would like to test.
*/
#define START_STATE IDLE
#define END_STATE LANDED

/*
    Initializing the state function pointer and the start and end states
*/
int(*state_function)(double[]);


/*
    Possible states should be included in the state_func array 
*/
state_func state_funcs[NUM_STATES] = 
    { idle_state, armed_state, burnout_state, 
      airbrakes_state, apogee_state, drogue_state,
      chute_state}; 
        
//Not includes states yet, may not be necessary.
//landed_state 
//liftoff_state,

state current_state = START_STATE;
return_code ret_code = REPEAT;

//Initializing BME and IMU sensor
BME280 Bme;
Adafruit_BNO055 IMU = Adafruit_BNO055(100, IMU_ADDRESS);

int const diode = 13;

/*
    Setting up the chip select on the SD card and
    initializing the datafile.
 */
uint8_t const SD_cspin = BUILTIN_SDCARD;
File dataFile;
const String filename = "Datafile.txt";
// frequency in Hz
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
  if (!Bme.beginI2C())
  {
    Serial.println("The BME sensor did not respond. Please check wiring.");
  }
  else {
    Serial.println("BME sensor successfully initialized");
  }
  delay(200);
  
  Serial.println("Setting up the IMU..");
  if (!IMU.begin())
  {
    Serial.println("The sensor did not respond. Please check wiring.");
  }
  else {
    Serial.println("IMU sensor successfully initialized");
  }
  delay(200);
  
  //Setup SD-card module
  if (!SD.begin(SD_cspin)) {
    Serial.println("initialization failed!");
    delay(1000);
    return;
  }
  else {
    delay(1000);
    Serial.println("SD card module successfully started");
    delay(2000); 
  }

  //Successfull setup -> lights diode
  LEDConfig(diode);
  LEDSetMode(diode, HIGH);


  //Delete file?
  Serial.println("Type 'd'/'k' to delete or keep log file ");

  const unsigned long startedWaiting = millis();
  const unsigned long waitNMillis = 5000;

  //Option to remove file using serial for waitNMillis milliseconds
  while(millis() - startedWaiting <= waitNMillis){
    String answer;
    answer = Serial.read(); 
    if (answer == "d"){
      SD.remove(filename.c_str());
      break;
    }
    else if (answer == "k") {
      break;
    }
  }
  Serial.println("Continuing..");

}

void loop()
{ 
  readSensors();
  
  //Running the state machine
  state_function = state_funcs[current_state];
  ret_code = return_code(state_function(data));
  current_state = lookup_transition(current_state, ret_code);
  
  //Starting writing to SD card when ARMED
  dataFile = SD.open("Datafile.txt", FILE_WRITE);
  if (dataFile && (current_state >= ARMED) && millis() - prevLogTime >= logEveryKMsec) {
    prevLogTime = millis();
    dataFile.println(createDataString(data));
  }
  else {
    Serial.println("Error opening file");
  }
  dataFile.close();

}

String createDataString(double data[NUM_TYPES]){
  String dataString = "";

  for (int i = 0; i < NUM_TYPES; i++){
    dataString += String(data[i]);
    dataString += ",";
  }

  return dataString;
}

/*
    Note that the IMU has declared x axis as the yaw axis, the y axis as the
    pitch axis and the z axis as the roll axis. This is corrected as:
      roll = x axis
      pitch = y axis
      yaw = z axis
*/
void readSensors(){
  //Update BMP280 sensor data
  data[BME_TEMP] = Bme.readTempC();
  data[PRESSURE] = Bme.readFloatPressure();
  data[ALTITUDE] = Bme.readFloatAltitudeMeters();

  //Temp IMU deg
  data[IMU_TEMP] = IMU.getTemp();

  //Extract Acceleration in m/s^2
  imu::Vector<3> accel = IMU.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  data[ACC_X] = accel.x();
  data[ACC_Y] = accel.y();
  data[ACC_Z] = accel.z();
  
  //Extract magnetometer data in uT
  imu::Vector<3> mag = IMU.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  data[MAG_X] = mag.x();
  data[MAG_Y] = mag.y();
  data[MAG_Z] = mag.z();

  //Extract euler angles in deg
  imu::Vector<3> euler = IMU.getVector(Adafruit_BNO055::VECTOR_EULER);
  data[ROLL] = euler.z();
  data[PITCH] = euler.y();
  data[YAW] = euler.x();

  //Extract angular rates in dps
  imu::Vector<3> rates = IMU.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  data[ANGULAR_VEL_X] = rates.z();
  data[ANGULAR_VEL_Y] = rates.y();
  data[ANGULAR_VEL_Z] = rates.x();

  //Extract gravity components
  imu::Vector<3> gravity = IMU.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  data[GRAVITY_ACC_X] = gravity.x();
  data[GRAVITY_ACC_Y] = gravity.y();
  data[GRAVITY_ACC_Z] = gravity.z();

  //linear acceleration = acceleration - gravity
  imu::Vector<3> linear_accel = IMU.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  data[LINEAR_ACCEL_X] = linear_accel.x();
  data[LINEAR_ACCEL_Y] = linear_accel.y();
  data[LINEAR_ACCEL_Z] = linear_accel.z();

  //Extract unit quaternions
  imu::Quaternion quaternions = IMU.getQuat(); 
  data[QUATERNION_X] = quaternions.x();
  data[QUATERNION_Y] = quaternions.y();
  data[QUATERNION_Z] = quaternions.z();
  data[QUATERNION_W] = quaternions.w();

  //data[TIMESTAMP]= event.timestamp;
  data[TIMESTAMP] = millis();
}
