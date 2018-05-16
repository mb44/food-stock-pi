#include "rf24stub.h"

void RF24Stub::setupRadio() {
}

RF24Stub::RF24Stub(const uint64_t pipes[2], IPacker *packer) :
packer(packer) {
}

RF24Stub::~RF24Stub() {
}

uint8_t RF24Stub::receive(int *scaleId, uint8_t *messageType, int *data) {
  //printf("Radio communication - Ready to receive\n");

/*
  // If there is data ready
  radio.startListening();

  while (1) {
    if (radio.available()) {

      uint8_t len;
      // Dump the payload until we've received everything
      while (radio.available()) {
        // printf("Reading...\n");
        // Fetch the payload, and see if this was the last one
        len = radio.getDynamicPayloadSize();
        radio.read(receivePayload, len);

        // Put a zero at the end for easy printing
        receivePayload[len] = 0;

        // Print to stdout
        //printf("Got payload size=%i value=%s\n\r", len, receivePayload);
      }
      radio.stopListening();
      
      packer->unpack(receivePayload, scaleId, messageType, data);

      if (*messageType==RADIO_RCV_MSG_TYPE_MEASUREMENT  
	|| *messageType==RADIO_RCV_MSG_TYPE_POWER_DOWN_REQ) {
        return 0;
      } else {
	return 1;
      }
    }
  }
*/
}

uint8_t RF24Stub::setUpdateFrequency(const int scaleId, const int updateFrequency) {
  // radio.stopListening();

  if (scaleId<0 || scaleId>MAX_CONTAINERS) {
    return 1;
  } else if (updateFrequency<0) {
    return 1;
  }

  packer->pack(sendPayload, scaleId, RADIO_SEND_MSG_TYPE_SET_UPDATE_FREQUENCY, updateFrequency);
  // radio.write(sendPayload, MAX_SEND_PAYLOAD_SIZE);

  // radio.startListening();
  return 0;
}

uint8_t RF24Stub::powerDown(const int scaleId) {
  if (scaleId<0 || scaleId>MAX_CONTAINERS) {
    return 1;
  }

  // radio.stopListening();

  packer->pack(sendPayload, scaleId, RADIO_SEND_MSG_TYPE_POWER_DOWN_RSP);

  // radio.write(sendPayload, MAX_SEND_PAYLOAD_SIZE);

  // radio.startListening();
  return 0;
}
