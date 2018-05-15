#ifndef RF24_ADAPTER_H
#define RF24_ADAPTER_H

#include "../../RF24.h"
#include "iradio.h"
#include "packer.h"

#define MIN_PAYLOAD_SIZE 1
#define MAX_RCV_PAYLOAD_SIZE 7
#define MAX_SEND_PAYLOAD_SIZE 7
#define PAYLOAD_SIZE_INCREMENTS_BY 1
#define NEXT_PAYLOAD_SIZE 1

class RF24Adapter : public IRadio {
  private:
    int minPayloadSize;
    int maxPayloadSize;
    int payloadSizeIncrementsBy;
    int nextPayloadSize;
    uint64_t radioPipes[2];
    // Adapting to this radio
    RF24 radio;
    IPacker *packer;
    char receivePayload[MAX_RCV_PAYLOAD_SIZE+1];
    char sendPayload[MAX_SEND_PAYLOAD_SIZE+1];
    void setupRadio();

  public:
    RF24Adapter(const uint64_t pipes[2], IPacker *packer);
    ~RF24Adapter();
    uint8_t receive(uint8_t *scaleId, int *messageType, int *data) override;
    uint8_t powerDown(const uint8_t scaleId) override;
    uint8_t setUpdateFrequency(const uint8_t scaleId, const int updateFrequency) override;
};

#endif  // RF24_ADAPTER_H 
