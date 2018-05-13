#include "packer.h"

Packer::~Packer() 
{}

void Packer::pack(char *payload, int scaleId, int messageType, int updateFrequency) {
  payload[0] = messageType;
  payload[1] = scaleId>>8;
  payload[2] = scaleId;
  payload[3] = updateFrequency>>24;
  payload[4] = updateFrequency>>16;
  payload[5] = updateFrequency>>8;
  payload[6] = updateFrequency;
}

void Packer::pack(char *payload, int scaleId, int messageType) {
  payload[0] = messageType;
  payload[1] = scaleId>>8;
  payload[2] = scaleId;
}
