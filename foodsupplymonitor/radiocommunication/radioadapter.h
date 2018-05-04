#ifndef _RADIO_COMMUNICATION_H
#define _RADIO_COMMUNICATION_H

#include "../../RF24.h"

#define MIN_PAYLOAD_SIZE 1
#define MAX_RCV_PAYLOAD_SIZE 7
#define MAX_SEND_PAYLOAD_SIZE 7
#define PAYLOAD_SIZE_INCREMENTS_BY 1
#define NEXT_PAYLOAD_SIZE 1

#include "iradiocommunication.h"

class RadioAdapter : public IRadioCommunication {
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
    RadioAdapter(const uint64_t pipes[2]);
    ~RadioAdapter();
    void send(char *sendPayload, uint8_t length);
    uint8_t receive(char *receivePayload);
};

#endif  // RADIO_ADAPTER_H 
