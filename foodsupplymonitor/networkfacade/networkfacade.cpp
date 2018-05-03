#include "networkfacade.h"
#include "../database/cjson.h"
#include <inttypes.h>

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
  char sendPayload[10]; //MAX_SEND_PAYLOAD_SIZE+1];
  printf("Handle radio communication\n");

  uint8_t length = 0;
  while (1) {
    length = radio->receive(receivePayload);
    printf("Got payload size=%i value=%s\n\r", length, receivePayload);
    
    for (int i=0; i<10; i++) {  
       printf("Byte %d: %d\n", i, receivePayload[i]); 

    }
/*
    //radio->send(receivePayload, length);
    sendPayload[0] = 97; //'L';
    sendPayload[1] = 4; //'a'; 
    sendPayload[2] = 5; //'r';
    sendPayload[3] = 6; //'s';
    sendPayload[4] = 7; //'m';
    sendPayload[5] = 8; //'o';
    radio->send(sendPayload, 10);
*/
/*
    // TODO
    // 1. Check msg type
    // 2. Query Database
    // 3. Send data to Uno
    uint8_t msgType = receivePayload[0];
    printf("Message type : %d\n", msgType);

    int id = receivePayload[1]<<8 | receivePayload[2];
    int measurementDecigrams;
    float measurementKilos;
    cJSON *updateFrequencyJSON;
    char *containerState;
    int updateFrequency;
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
          // 1. Get container state
          measurementDecigrams = receivePayload[3]<<24 | receivePayload[4]<<16 | receivePayload[5]<<8 | receivePayload[6];
          // Convert from decigrams to Kilograms
          measurementKilos = measurementDecigrams / 100.0;

          //printf("Measurement: %d grams\n", measurement);
          //printf("Measurement in kilos: %f\n", measurementKilos);
	  

	  // 2. Get container state
          reply = db->getContainerState(id);
          containerState = reply->valuestring;
          //printf("Container state: %s\n", containerState);

	  // 3. Set a) Measurement b) emptyContainerWeight 3) maximumCapacity
          if (strcmp(containerState, "measure") == 0) {
	    db->setMeasurement(id, measurementKilos);
	  } else if (strcmp(containerState, "emptyContainerWeight") == 0) {
	    db->setEmptyContainerWeight(id, measurementKilos);
	  } else if (strcmp(containerState, "maximumCapacity") == 0) {
	    db->setMaximumCapacity(id, measurementKilos);
	  }


	  // 4. Get update freqency from DB
          cJSON_Delete(reply);
          reply = db->getUpdateFrequency(id);

	  const char *temp = cJSON_Print(reply);


	  printf("Reply: %s\n", temp);
	  updateFrequency = reply->valueint;
	  cJSON_Delete(reply);
          printf("Update frequency: %d\n", updateFrequency);

          sendPayload[0] = RADIO_SEND_MSG_TYPE_SET_UPDATE_FREQUENCY;
	  // Add Id
	  sendPayload[1] = id>>8;
	  sendPayload[2] = id;
	  // Add UpdateFrequency
	  sendPayload[3] = updateFrequency>>8;
	  sendPayload[4] = updateFrequency;

	  printf("Sending: \n");
	  printf("Byte 0: %d\n: ", sendPayload[0]);
	  printf("Byte 1: %d\n: ", sendPayload[1]);
	  printf("Byte 2: %d\n: ", sendPayload[2]);
	  printf("Byte 3: %d\n: ", sendPayload[3]);
	  printf("Byte 4: %d\n: ", sendPayload[4]);

//	  printf("Sending.\n");
	  sendPayload[0] = 2;
	  sendPayload[1] = 0;
	  sendPayload[2] = 1;
	  sendPayload[3] = 0;
	  sendPayload[4] = 60;

	  // 5. Send reply to Scale
	  radio->send(sendPayload, MAX_SEND_PAYLOAD_SIZE);

          //free(containerState);
            
	  break;
        //default:
          //break;
    }
*/
  }
}
