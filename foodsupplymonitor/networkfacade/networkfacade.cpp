#include "networkfacade.h"
#include <inttypes.h>

NetworkFacade::NetworkFacade(IRadio *r, IDatabase *d) 
  : radio(r),
    db(d)
{}

NetworkFacade::~NetworkFacade() {
}

void NetworkFacade::handleNetwork() {
  char receivePayload[MAX_RCV_PAYLOAD_SIZE+1];

  // Listen, forever
  int scaleId = 0;
  uint8_t msgType = 0;
  int data = 0;
  uint8_t error = 1;

  while (1) {
    error = radio->receive(&scaleId, &msgType, &data);
    if (error) {
	continue;
    }
    

    printf("Got payload value=%s\n\r", receivePayload);
    
    //for (int i=0; i<10; i++) {  
    //   printf("Byte %d: %d\n", i, receivePayload[i]); 
    //}


    printf("Received a request\n");
    // 1. Check msg type
    // 2. Query Database
    // 3. Send reply to Uno
    //uint8_t msgType = receivePayload[0];
    //int scaleId = receivePayload[1]<<8 | receivePayload[2];
    int measurementDecigrams;
    float measurementKilos;
    char containerState[30];
    int updateFrequencySeconds;
    uint8_t exists = 0;

    switch (msgType) {
        case RADIO_RCV_MSG_TYPE_MEASUREMENT:
	  // 1. Create container in db if not already there
	  db->containerItemExists(scaleId, &exists);
          if (exists == CONTAINER_ID_NOT_EXISTS) {
	    db->createContainerItem(scaleId);
	  }
          // 2. Extract measurement
          measurementDecigrams = data;
          // Convert from decigrams to Kilograms
          measurementKilos = measurementDecigrams / 100.0;
	  // 3. Get containerState from database
          db->getContainerState(scaleId, containerState);
          // printf("Container state: %s\n", containerState);

	  // 4. Set a) Measurement b) emptyContainerWeight 3) maximumCapacity
          if (strcmp(containerState, CURRENT_AMOUNT) == 0) {
	    db->setCurrentAmount(scaleId, measurementKilos);
	  } else if (strcmp(containerState, EMPTY_CONTAINER_WEIGHT) == 0) {
	    db->setEmptyContainerWeight(scaleId, measurementKilos);
	    db->setContainerState(scaleId, CURRENT_AMOUNT);
	  } else if (strcmp(containerState, MAXIMUM_CAPACITY) == 0) {
	    db->setMaximumCapacity(scaleId, measurementKilos);
	    db->setContainerState(scaleId, CURRENT_AMOUNT);
	  }

	  // 5. Get update freqency from DB
          printf("scale id: %d\n", scaleId);
          db->getUpdateFrequency(scaleId, &updateFrequencySeconds);
          printf("Update frequency: %d\n", updateFrequencySeconds);

	  // 5. Send reply to Scale
	  radio->setUpdateFrequency(scaleId, updateFrequencySeconds);
	  //radio->send(sendPayload, MAX_SEND_PAYLOAD_SIZE);
	  break;
    
	 case RADIO_RCV_MSG_TYPE_POWER_DOWN_REQ:
           break;
           // Delete container
           //db->deleteContainerItem(scaleId);
           radio->powerDown(scaleId);
    }
  }
}
