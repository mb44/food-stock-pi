#include "networkfacade.h"


NetworkFacade::NetworkFacade(const uint64_t addrMe, const uint64_t addrOther) 
: addrMe(addrMe),
  addrOther(addrOther)
{
  db = new FirebaseAdapter("firebaseConfig.txt");
  radio = new RadioCommunication(addrMe, addrOther); 
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
