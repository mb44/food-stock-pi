#ifndef IPACKER_H
#define IPACKER_H

#include "../defines.h"
#include <stdint.h>

class IPacker {
  public:
    virtual ~IPacker() {}
    virtual uint8_t pack(char *payload, const int scaleId, const uint8_t messageType) = 0;
    virtual uint8_t pack(char *payload, int scaleId, uint8_t messageType, int updateFrequency) = 0;
    virtual uint8_t unpack(const char *payload, int *scaleId, uint8_t *messageType, int *data) = 0;
};

#endif // IPACKER_H
