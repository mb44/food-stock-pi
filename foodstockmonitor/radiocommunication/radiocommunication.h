#ifndef _RADIO_COMMUNICATION_H
#define _RADIO_COMMUNICATION_H

#include "../../RF24.h"

#define MIN_PAYLOAD_SIZE 1
#define MAX_RCV_PAYLOAD_SIZE 7
#define MAX_SEND_PAYLOAD_SIZE 5
#define PAYLOAD_SIZE_INCREMENTS_BY 1
#define NEXT_PAYLOAD_SIZE 1

#include "iradiocommunication.h"

//class IRadioCommunication;

class RadioCommunication : public IRadioCommunication {
//class RadioCommunication { 
  private:
    int minPayloadSize;
    int maxPayloadSize;
    int payloadSizeIncrementsBy;
    int nextPayloadSize;
    char receivePayload[MAX_RCV_PAYLOAD_SIZE+1];
    uint64_t radioPipes[2];
    // Adapting to this radio
    RF24 radio;

  public:
    void setupRadio();
    RadioCommunication(const uint64_t pipes[2]);
    ~RadioCommunication();
    void send(char *sendPayload, uint8_t length); //void send() override;
    uint8_t receive(char *receivePayload); //void receive() override;
};

#endif  // RADIO_COMMUNICATION_H 
