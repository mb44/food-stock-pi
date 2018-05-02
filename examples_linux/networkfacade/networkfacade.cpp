#include "networkfacade.h"
#include "../database/cjson.h"
#include <inttypes.h>
//#include <iostream>

NetworkFacade::NetworkFacade(const uint64_t pipes[2]) 
{
  db = new FirebaseAdapter("firebaseConfig.txt");
  radio = new RadioCommunication(pipes); 
}

NetworkFacade::~NetworkFacade() {
  delete db;
  delete radio;
}

void NetworkFacade::handleNetwork() {
  char receivePayload[MAX_RCV_PAYLOAD_SIZE+1];

  printf("Handle radio communication\n");

  uint8_t length = 0;
  while (1) {
    length = radio->receive(receivePayload);
    printf("Got payload size=%i value=%s\n\r", length, receivePayload);
    
    for (int i=0; i<10; i++) {  
      printf("Byte %d: %d\n", i, receivePayload[i]); 

    }

    radio->send(receivePayload, length);

    // TODO
    // 1. Check msg type
    // 2. Query Database
    // 3. Send data to Uno
    uint8_t msgType = receivePayload[0];
    printf("Message type : %d\n", msgType);

    int id = receivePayload[1]<<8 | receivePayload[2];
    int measurement;
    cJSON *reply;
    switch (msgType) {
	case RADIO_RCV_MSG_TYPE_GET_CONTAINER_ID:
          // Get container id
          reply = db->createContainerItem();
          delete reply;
          break;
        case RADIO_RCV_MSG_TYPE_DELETE_CONTAINER:
          break;
          // Delete container
        case RADIO_RCV_MSG_TYPE_MEASUREMENT:
          // Send measurement
	  //const cJSON* reply;
          measurement = receivePayload[3]<<24 | receivePayload[4]<<16 | receivePayload[5]<<8 | receivePayload[6];
          // Convert from decigrams to grams          
          measurement /= 10;

          printf("Measurement: %d grams\n", measurement);
        //default:
          //break;
    }
  }
}
