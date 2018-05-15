#ifndef IPACKER_H
#define IPACKER_H

#include <stdint.h>

class IPacker {
  public:
    virtual ~IPacker() {}
    virtual uint8_t pack(char *payload, const uint8_t scaleId, const int messageType) = 0;
    virtual uint8_t pack(char *payload, uint8_t scaleId, int messageType, int updateFrequency) = 0;
    virtual uint8_t unpack(const char *payload, uint8_t *scaleId, int *messageType, int *data) = 0;
};

#endif // IPACKER_H
