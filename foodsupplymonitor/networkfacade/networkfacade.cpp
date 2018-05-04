#include "networkfacade.h"
#include "../database/cjson.h"
#include <inttypes.h>

NetworkFacade::NetworkFacade(const uint64_t pipes[2]) 
{
  db = new FirebaseAdapter("firebaseConfig.txt");
  radio = new RadioAdapter(pipes); 
}

NetworkFacade::~NetworkFacade() {
  delete db;
  delete radio;
}

void NetworkFacade::handleNetwork() {
  char receivePayload[MAX_RCV_PAYLOAD_SIZE+1];
  char sendPayload[MAX_SEND_PAYLOAD_SIZE+1];
  printf("Handle radio communication\n");

  uint8_t length = 0;
  // Listen, forever
  while (1) {
    length = radio->receive(receivePayload);
    printf("Got payload size=%i value=%s\n\r", length, receivePayload);
    
    for (int i=0; i<10; i++) {  
       printf("Byte %d: %d\n", i, receivePayload[i]); 

    }

   // radio->send(receivePayload, length);
    //  TODO
    // 1. Check msg type
    // 2. Query Database
    // 3. Send data to Uno
    uint8_t msgType = receivePayload[0];
    printf("Message type : %d\n", msgType);

    int id = receivePayload[1]<<8 | receivePayload[2];
    int newContainerId;
    int measurementDecigrams;
    float measurementKilos;
    char *containerState;
    int updateFrequencySeconds;
    cJSON *reply;
    switch (msgType) {
	case RADIO_RCV_MSG_TYPE_GET_CONTAINER_ID:
          // Get container id from database
          newContainerId = db->createContainerItem();

	  // Set message type
	  sendPayload[0] = 0;

	  // Set scale id
	  sendPayload[1] = receivePayload[2];
	  sendPayload[2] = receivePayload[3];

	  // Set new id
	  sendPayload[3] = newContainerId>>8;
	  sendPayload[4] = newContainerId;

	  printf("Send payload:\n");
	  printf("Byte 0: %d\n", sendPayload[0]);
	  printf("Byte 1: %d\n", sendPayload[1]);
	  printf("Byte 2: %d\n", sendPayload[2]);
	  printf("Byte 3: %d\n", sendPayload[3]);
	  printf("Byte 4: %d\n", sendPayload[5]);

	  radio->send(sendPayload, MAX_SEND_PAYLOAD_SIZE);
          break;
        case RADIO_RCV_MSG_TYPE_DELETE_CONTAINER:
          break;
          // Delete container
        case RADIO_RCV_MSG_TYPE_MEASUREMENT:
          // 1. Extract measurement
          measurementDecigrams = receivePayload[3]<<24 | receivePayload[4]<<16 | receivePayload[5]<<8 | receivePayload[6];
          // Convert from decigrams to Kilograms
          measurementKilos = measurementDecigrams / 100.0;
	  // 2. Get containerState from database
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
          delete containerState;
          //	cJSON_Delete(reply);
          reply = db->getUpdateFrequency(id);
	  //const char *temp = cJSON_Print(reply);
	  //printf("Reply: %s\n", temp);
	  updateFrequencySeconds = reply->valueint;
	  cJSON_Delete(reply);
          printf("Update frequency (seconds): %d\n", updateFrequencySeconds);

          sendPayload[0] = RADIO_SEND_MSG_TYPE_SET_UPDATE_FREQUENCY;
	  // Add Id
	  sendPayload[1] = id>>8;
	  sendPayload[2] = id;
	  // Add UpdateFrequency
	  sendPayload[3] = updateFrequencySeconds>>24;
	  sendPayload[4] = updateFrequencySeconds>>16;
	  sendPayload[5] = updateFrequencySeconds>>8;
	  sendPayload[6] = updateFrequencySeconds;

	  printf("Sending: \n");
	  printf("Byte 0: %d\n: ", sendPayload[0]);
	  printf("Byte 1: %d\n: ", sendPayload[1]);
	  printf("Byte 2: %d\n: ", sendPayload[2]);
	  printf("Byte 3: %d\n: ", sendPayload[3]);
	  printf("Byte 4: %d\n: ", sendPayload[4]);
	  printf("Byte 5: %d\n: ", sendPayload[5]);
	  printf("Byte 6: %d\n: ", sendPayload[6]);

	  // 5. Send reply to Scale
	  radio->send(sendPayload, MAX_SEND_PAYLOAD_SIZE);
	  break;
    }
  }
}
