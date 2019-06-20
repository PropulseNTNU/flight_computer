#include "bluetooth.h"


RF24 conn(CE_PIN, CSN_PIN); 


void initMessage(double* data, int numberOfSensors){
  for(int i = 0; i < numberOfSensors; i++){
    data[i] = 0.0;
  }  
}

int setupBle(double* data, int NUM_SENSORS){
  Serial.begin(9600);
  SPI.setSCK(SCK_PIN);  
  conn.begin();
  
  conn.setPALevel(RF24_PA_MAX);
  conn.setChannel(0x76);
  conn.openWritingPipe(0xF0F0F0F0E1LL);
  const uint64_t pipe = (0xE8E8F0F0E1LL);
  conn.openReadingPipe(1, pipe);

  conn.enableDynamicPayloads();
  conn.powerUp();
  initMessage(data, NUM_SENSORS);
  return 1;    
}


char* retriveMessageBle(){
  conn.startListening();
  char receivedMessage[32] = {0};
  char * buf = (char *) malloc (sizeof(receivedMessage));
  if(conn.available()){
    conn.read(receivedMessage, sizeof(receivedMessage));
    //Serial.println("Recievedmsg: ");
    //Serial.println(receivedMessage);
    //sprintf(buf, receivedMessage);
    strcpy (buf, receivedMessage);
    conn.stopListening();
    return buf;     
  }
  //Serial.println("no connection");
  delay(50);
  free(buf);
  return 0;
}

void sendMessage(const char message){
  conn.write(&message, sizeof(message));
  delay(1000);
}


int messageFromPayload(double* data){
  char* message =  (retriveMessageBle());
  free(retriveMessageBle());	
  int index = 0;
  index = strlen(message);
  String messageID = "";
  //Serial.println("This msg is being handled: ");
  //Serial.println(message); 
  if(index > 2){
    uint8_t messageIDFirstDigit = uint8_t(message[index-2])- 48; //ASCII fixing
    uint8_t messageIDSecondDigit = uint8_t(message[index-1]) - 48; //ASCII fixing
    messageID = String(messageIDFirstDigit) + String(messageIDSecondDigit);
     
    if(messageIDFirstDigit == 253){ //ASCII fix removing '-'
      messageID = String(messageIDSecondDigit);
    }
    message[index -2] = '\0';
    double msg = atof(message);
    int id = messageID.toInt(); 
    id = mapIDOfSensors(id); 
    Serial.println("ID: ");
    Serial.println(id);	   
    data[id] = msg;
    return 1;
  }
      
  return 0;
}

void updateDataFromBle(double* data){
  //for(int i = 0; i < (NUMBER_OF_SENSORS - 1); i++){
    int checkReading = messageFromPayload(data);
    //if(!(checkReading)){
      //Serial.println("No reading");;
    //}
    
  //}

}

int mapIDOfSensors(int id){
    id = id - 1;
    switch(id){
    case ATIME:              return TIME;
    case AROLL:              return TROLL;
    case APITCH:             return TPITCH;
    case AYAW:               return TYAW;
    case AACCELERATION_X:    return 20;
    case AACCELERATION_Y:    return TACCELERATION_Y;
    case AACCELERATION_Z:    return 20;
    case ACOMPASS_X:         return 20;
    case ACOMPASS_Y:         return 20;    
    case ACOMPASS_Z: 	     return 20;
    case ATEMPERATURES:      return 20;
    case AHUMIDITY:          return 20;
    case AALTITUDE:          return TALTITUDE;
    case APRESSURE:          return 20;
    case AGAS:               return 20;
    case ATEMP_ACCUR_SENS:   return 20;
    
    default:   Serial.println("Not valid!");
    }
}

