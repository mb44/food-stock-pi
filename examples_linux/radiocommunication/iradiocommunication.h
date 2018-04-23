#ifdef _IRADIO_COMMUNICATION
#define _IRADIO_COMMUNICATION

class IRadioCommunication {
  public:
    virtual ~IRadioCommunication() {};
    virtual void send() = 0;
    virtual void receive() = 0;
};

#endif // _IRADIO_COMMMUNICATION
