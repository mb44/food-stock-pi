#ifdef _IRADIO_COMMUNICATION
#define _IRADIO_COMMUNICATION

class IRadioCommunication {
  public:
    virtual ~IRadioCommunication() {};
    virtual void send(char *sendPayload, uint8_t length) = 0;
    virtual uint8_t receive(char receivePayload) = 0;
};

#endif // _IRADIO_COMMMUNICATION
