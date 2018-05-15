#include "radiostub.h"

void RadioStub::setupRadio() {
}

RadioStub::RadioStub(const uint64_t pipes[2]) {
}

RadioStub::~RadioStub() {
}

uint8_t RadioStub::receive(int *scaleId, uint8_t *messageType, int *data) {
/*
  printf("Radio communication - Ready to receive\n");
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
      return len;
    }
  }
*/
  return 1;
}


uint8_t RadioStub::setUpdateFrequency(const int scaleId, int updateFrequency) {
  return 1;
}


uint8_t RadioStub::powerDown(const int scaleId) {
  return 1;
}
