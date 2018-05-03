#ifndef _IRADIO_COMMUNICATION
#define _IRADIO_COMMUNICATION

#include <stdint.h>

#define RADIO_RCV_MSG_TYPE_GET_CONTAINER_ID 0
#define RADIO_RCV_MSG_TYPE_DELETE_CONTAINER 1
#define RADIO_RCV_MSG_TYPE_MEASUREMENT 2


#define RADIO_SEND_MSG_TYPE_SET_CONTAINER_ID 0
#define RADIO_SEND_MSG_TYPE_POWER_DOWN 1
#define RADIO_SEND_MSG_TYPE_SET_UPDATE_FREQUENCY 2

class IRadioCommunication {
  public:
    virtual ~IRadioCommunication() {};
    virtual void send(char *sendPayload, uint8_t length) = 0;
    virtual uint8_t receive(char *receivePayload) = 0;
};

#endif // _IRADIO_COMMMUNICATION
