#ifndef _RADIO_COMMUNICATIONFACADE_H
#define _RADIO_COMMUNICATIONFACADE_H

#include "radiocommunication.h"

class RadioCommunicationFacade { 
  private:
    RadioCommunication *radio;
    uint64_t addrMe;
    uint64_t addrOther;
   
  public:
    void setupRadio();
    RadioCommunicationFacade(const uint64_t addrMe, const uint64_t addrOther);
    ~RadioCommunicationFacade();
    void handleRadioCommunication(); 
};

#endif  // RADIO_COMMUNICATIONFACADE_H 
