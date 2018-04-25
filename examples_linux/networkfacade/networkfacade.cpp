#include "networkfacade.h"


NetworkFacade::NetworkFacade(const uint64_t pipeMe, const uint64_t pipeOther) 
{
  db = new FirebaseAdapter("firebaseConfig.txt");
  radio = new RadioCommunication(pipeMe, pipeOther); 
}

NetworkFacade::~NetworkFacade() {
  delete db;
  delete radio;
}

void NetworkFacade::handleNetwork() {
  char receivePayload[MAX_PAYLOAD_SIZE+1];

  printf("Handle radio communication\n");

  uint8_t length = 0;
  while (1) {
    length = radio->receive(receivePayload);
    printf("Got payload size=%i value=%s\n\r", length, receivePayload);

    // TODO
    // 1. Check msg type
    // 2. Query Database
    // 3. Send data to Uno
  }
}
