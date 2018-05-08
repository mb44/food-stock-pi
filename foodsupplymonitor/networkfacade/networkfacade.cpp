#include "networkfacade.h"
#include <inttypes.h>

NetworkFacade::NetworkFacade(const uint64_t pipes[2]) {
  db = new FirebaseAdapter("firebaseConfig.txt");
  radio = new RF24Adapter(pipes); 
}

NetworkFacade::~NetworkFacade() {
  delete db;
  delete radio;
}

void NetworkFacade::handleNetwork() {
  char receivePayload[MAX_RCV_PAYLOAD_SIZE+1];
  //char sendPayload[MAX_SEND_PAYLOAD_SIZE+1];

  uint8_t length = 0;

  printf("Network facade\n");


 /* //db->createContainerItem(13);
  //db->deleteContainerItem(13);
  // db->setMeasurement(3, 13.37);
  //db->setEmptyContainerWeight(3, 5.5);
  //  db->setMaximumCapacity(3, 11.23);
  // db->setContainerState(3, "maximumCapacity");
  //int updateFreq;
  //db->getUpdateFrequency(3, &updateFreq);
  //printf("UPDATE FREQ: %d\n", updateFreq);
  char containerState[30];

  db->getContainerState(3, containerState);
  printf("CONTAINER STATE: %s\n", containerState);

  if (strcmp(containerState, "measure") == 0) {
    printf("measuring!!!\n");
  } else {
    printf("errrroooo\n");
}
*/

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

    int scaleId = receivePayload[1]<<8 | receivePayload[2];
    int measurementDecigrams;
    float measurementKilos;
    char containerState[30];
    int updateFrequencySeconds;
    switch (msgType) {
        case RADIO_RCV_MSG_TYPE_MEASUREMENT:
          // 1. Extract measurement
          measurementDecigrams = receivePayload[3]<<24 | receivePayload[4]<<16 | receivePayload[5]<<8 | receivePayload[6];
          // Convert from decigrams to Kilograms
          measurementKilos = measurementDecigrams / 100.0;
	  // 2. Get containerState from database
          db->getContainerState(scaleId, containerState);
          //printf("Container state: %s\n", containerState);

	  // 3. Set a) Measurement b) emptyContainerWeight 3) maximumCapacity
          if (strcmp(containerState, CURRENT_AMOUNT) == 0) {
	    db->setMeasurement(scaleId, measurementKilos);
	  } else if (strcmp(containerState, EMPTY_CONTAINER_WEIGHT) == 0) {
	    db->setEmptyContainerWeight(scaleId, measurementKilos);
	    db->setContainerState(scaleId, CURRENT_AMOUNT);
	  } else if (strcmp(containerState, MAXIMUM_CAPACITY) == 0) {
	    db->setMaximumCapacity(scaleId, measurementKilos);
	    db->setContainerState(scaleId, CURRENT_AMOUNT);
	  }

	  // 4. Get update freqency from DB
          db->getUpdateFrequency(scaleId, &updateFrequencySeconds);
          printf("Update frequency (seconds): %d\n", updateFrequencySeconds);

/*
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
*/
	  // 5. Send reply to Scale
	  radio->setUpdateFrequency(scaleId, updateFrequencySeconds);
	  //radio->send(sendPayload, MAX_SEND_PAYLOAD_SIZE);
	  break;
    
	 case RADIO_RCV_MSG_TYPE_DELETE_CONTAINER:
           break;
           // Delete container
           //db->deleteContainerItem(scaleId);
           radio->powerDown(scaleId);
    }
  }
}
