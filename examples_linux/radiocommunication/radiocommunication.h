#ifndef _RADIO_COMMUNICATION_H
#define _RADIO_COMMUNICATION_H

//#include "iradiocommunication.h"

// class IRadioCommunication;

//class RadioCommunication : public IRadioCommunication {
class RadioCommunication { 
  public:
    RadioCommunication();
    ~RadioCommunication();
    void send(char *msg); //void send() override;
    void receive(char *msg); //void receive() override;
};

#endif  // RADIO_COMMUNICATION_H 
