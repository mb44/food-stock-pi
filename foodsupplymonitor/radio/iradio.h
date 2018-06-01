#ifndef IRADIO_H
#define IRADIO_H

#include "../defines.h"
#include "radiodefines.h"
#include <stdint.h>

/*! \file iradio.h
    \brief Interface for radio communication.
*/
class IRadio {
  public:
    virtual ~IRadio() {}
    virtual uint8_t receive(int *scaleId, uint8_t *messageType, int *data) = 0;
    virtual uint8_t setUpdateFrequency(const int scaleId, const int updateFrequency) = 0;
    virtual uint8_t powerDown(const int scaleId) = 0;
};

#endif // IRADIO_H
