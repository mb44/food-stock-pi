#ifndef PACKER_H
#define PACKER_H

#include "ipacker.h"

class Packer : public IPacker{
  public:
    ~Packer();
    uint8_t pack(char *payload, const uint8_t scaleId, const int messageType) override;
    uint8_t pack(char *payload, const uint8_t scaleId, const int messageType, const int updateFrequency) override;
    uint8_t unpack(const char *payload, uint8_t *scaleId, int *messageType, int *data);
};

#endif // PACKER_H
