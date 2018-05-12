#include "radiostub.h"

void RadioStub::setupRadio() {
}

RadioStub::RadioStub(const uint64_t pipes[2]) {
}

RadioStub::~RadioStub() {
}

/*
void RadioAdapter::send(char *sendPayload, uint8_t length) {
  radio.stopListening();

  radio.write(sendPayload, length);
  radio.startListening();
}
*/

void RadioStub::pack(int scaleId, int messageType, int updateFrequency) {
  sendPayload[0] = messageType;
  sendPayload[1] = scaleId>>8;
  sendPayload[2] = scaleId;
  sendPayload[3] = updateFrequency>>24;
  sendPayload[4] = updateFrequency>>16;
  sendPayload[5] = updateFrequency>>8;
  sendPayload[6] = updateFrequency;

}

void RadioStub::pack(int scaleId, int messageType) {
  sendPayload[0] = messageType;
  sendPayload[1] = scaleId>>8;
  sendPayload[2] = scaleId;
}

uint8_t RadioStub::receive(char *receivePayload) {
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

void RadioStub::setUpdateFrequency(int scaleId, int updateFrequency) {
}

void RadioStub::powerDown(int scaleId) {
}
