#ifndef IRADIO_H
#define IRADIO_H

#include "radiodefines.h"
#include <stdint.h>

class IRadio {
  public:
    virtual ~IRadio() {}
    virtual uint8_t setUpdateFrequency(const uint8_t scaleId, const int updateFrequency) = 0;
    virtual uint8_t powerDown(const uint8_t scaleId) = 0;
    virtual uint8_t receive(uint8_t *scaleId, int *messageType, int *data) = 0;
};

#endif // IRADIO_H
