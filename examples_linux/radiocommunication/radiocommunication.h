#ifndef _RADIO_COMMUNICATION_H
#define _RADIO_COMMUNICATION_H

#include "../../RF24.h"

#define MIN_PAYLOAD_SIZE 1
#define MAX_PAYLOAD_SIZE 32
#define PAYLOAD_SIZE_INCREMENTS_BY 1
#define NEXT_PAYLOAD_SIZE 1

//#include "iradiocommunication.h"

// class IRadioCommunication;

  class RF24;

//class RadioCommunication : public IRadioCommunication {
class RadioCommunication { 
  private:
    int minPayloadSize;
    int maxPayloadSize;
    int payloadSizeIncrementsBy;
    int nextPayloadSize;
    char receivePayload[MAX_PAYLOAD_SIZE+1];
    uint64_t addrMe;
    uint64_t addrOther;
    // Adapting to this radio
    RF24 radio;

  public:
    void setupRadio();
    RadioCommunication(const uint64_t addrMe, const uint64_t addrOther);
    ~RadioCommunication();
    void send(char *sendPayload); //void send() override;
    void receive(char *receivePayload); //void receive() override;
};

#endif  // RADIO_COMMUNICATION_H 
