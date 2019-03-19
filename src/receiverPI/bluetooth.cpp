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
    strcpy (buf, receivedMessage);
    conn.stopListening();
    return buf;     
  }
  delay(200);
  //free(receivedMessage);
  return 0;
}


void sendMessage(const char message){
  conn.write(&message, sizeof(message));
  delay(1000);
}


int messageFromPayload(double* data){
  char* message =  (retriveMessageBle());
  int index = 0;
  index = strlen(message);
  String messageID = ""; 
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
        
    data[id] = msg;
    return 1;
  }
      
  delay(200);
  return 0;
}

void updateDataFromBle(double* data){
  for(int i = 0; i < (NUMBER_OF_SENSORS - 1); i++){
    int checkReading = messageFromPayload(data);
    if(!(checkReading)){
      Serial.println("No reading");;
    }
    
  }

}

