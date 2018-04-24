#ifndef _RADIO_COMMUNICATION_H
#define _RADIO_COMMUNICATION_H

#include "../../RF24.h"

#define MIN_PAYLOAD_SIZE 1
#define MAX_PAYLOAD_SIZE 32
#define PAYLOAD_SIZE_INCREMENTS_BY 1
#define NEXT_PAYLOAD_SIZE 1

//#include "iradiocommunication.h"

// class IRadioCommunication;

//class RadioCommunication : public IRadioCommunication {
class RadioCommunication { 
  private:
    // +1 to allow room a terminating NULL char
    int minPayloadSize;
    int maxPayloadSize;
    int payloadSizeIncrementsBy;
    int nextPayloadSize;
    // +1 to allow room for a terminating NULL char
    char receive_payload[MAX_PAYLOAD_SIZE+1];
    uint64_t addrMe;
    uint64_t addrOther;

  public:
    void init();
    RadioCommunication(const uint64_t nodeMe, const uint64_t nodeOther);
    ~RadioCommunication();
    void send(char *msg); //void send() override;
    void receive(char *msg); //void receive() override;
};

#endif  // RADIO_COMMUNICATION_H 
