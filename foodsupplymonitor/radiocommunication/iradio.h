#ifndef IRADIO_H
#define IRADIO_H

#include "radiodefines.h"
#include <stdint.h>

class IRadio {
  public:
    virtual ~IRadio() {};
    virtual void setUpdateFrequency(int scaleId, int updateFrequency) = 0;
    virtual void powerDown(int scaleId) = 0;
    //virtual void send(char *sendPayload, uint8_t length) = 0;
    virtual uint8_t receive(char *receivePayload) = 0;
};

#endif // IRADIO_H
