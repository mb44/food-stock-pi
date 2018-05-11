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
    printf("Message type: %d\n", msgType);

    int scaleId = receivePayload[1]<<8 | receivePayload[2];
    int measurementDecigrams;
    float measurementKilos;
    char containerState[30];
    int updateFrequencySeconds;
    int exists = 0;

    switch (msgType) {
        case RADIO_RCV_MSG_TYPE_MEASUREMENT:
	  // 1. Create container in db if not already there
	  db->containerItemExists(scaleId, &exists);
          if (exists == CONTAINER_ID_NOT_EXISTS) {
	    db->createContainerItem(scaleId);
	  }
          // 2. Extract measurement
          measurementDecigrams = receivePayload[3]<<24 | receivePayload[4]<<16 | receivePayload[5]<<8 | receivePayload[6];
          // Convert from decigrams to Kilograms
          measurementKilos = measurementDecigrams / 100.0;
	  // 3. Get containerState from database
          db->getContainerState(scaleId, containerState);
          //printf("Container state: %s\n", containerState);

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
          printf("Update frequency (seconds): %d\n", updateFrequencySeconds);

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
