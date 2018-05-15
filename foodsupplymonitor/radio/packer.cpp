#include "packer.h"

Packer::~Packer() 
{}

uint8_t Packer::pack(char *payload, const uint8_t scaleId, const int messageType, const int updateFrequency) {
  payload[0] = messageType;
  payload[1] = scaleId>>8;
  payload[2] = scaleId;
  payload[3] = updateFrequency>>24;
  payload[4] = updateFrequency>>16;
  payload[5] = updateFrequency>>8;
  payload[6] = updateFrequency;
  return 0;
}

uint8_t Packer::pack(char *payload, const uint8_t scaleId, const int messageType) {
  payload[0] = messageType;
  payload[1] = scaleId>>8;
  payload[2] = scaleId;
  return 0;
}

uint8_t Packer::unpack(const char *payload, uint8_t *scaleId, int *messageType, int *data) {
  *messageType = payload[0];
  *scaleId = payload[2];
  *scaleId = payload[1]<<8;
  *data = payload[3]<<24 | payload[4]<<16 | payload[5]<<8 | payload[6]; 
  return 0;
}
