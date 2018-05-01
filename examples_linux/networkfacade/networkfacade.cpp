#include "networkfacade.h"
#include "../database/cjson.h"

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
    long measurement;
    cJSON *reply;
    switch (msgType) {
	case 0:
          // Get container id
          reply = db->createContainerItem();
          delete reply;
          break;
        case 1:
          break;
          // Delete container
        case 2:
          // Send measurement
	  //const cJSON* reply;

          measurement = receivePayload[3]<<32 | receivePayload[4]<<16 | receivePayload[5]<<8 | receivePayload[6];
          // Convert from decigrams to grams          
          measurement /= 10;


          //printf("Size of long: %l\n ", sizeof(long));
          printf("Measurement: %ld grams\n", measurement);
        //default:
          //break;
    }
  }
}
