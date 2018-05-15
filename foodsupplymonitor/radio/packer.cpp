#include "packer.h"

Packer::~Packer() 
{}

uint8_t Packer::pack(char *payload, const int scaleId, const uint8_t messageType, const int updateFrequency) {
  if (scaleId < 0 || scaleId > MAX_CONTAINERS) {
    return 1;
  } else if (updateFrequency < 0) {
    return 1;
  }

  payload[0] = messageType;
  payload[1] = scaleId>>8;
  payload[2] = scaleId;
  payload[3] = updateFrequency>>24;
  payload[4] = updateFrequency>>16;
  payload[5] = updateFrequency>>8;
  payload[6] = updateFrequency;
  return 0;
}

uint8_t Packer::pack(char *payload, const int scaleId, const uint8_t messageType) {
  if (scaleId < 0 || scaleId > MAX_CONTAINERS) {
    return 1;
  }

  payload[0] = messageType;
  payload[1] = scaleId>>8;
  payload[2] = scaleId;
  return 0;
}

uint8_t Packer::unpack(const char *payload, int *scaleId, uint8_t *messageType, int *data) {
  *scaleId = payload[2];
  *scaleId = payload[1]<<8;

  if (*scaleId < 0 || *scaleId > MAX_CONTAINERS) {
    return 1;
  }

  *messageType = payload[0];

  *data = payload[3]<<24 | payload[4]<<16 | payload[5]<<8 | payload[6]; 
  return 0;
}
