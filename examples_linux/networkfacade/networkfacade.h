#ifndef _NETWORK_FACADE_H
#define _NETWORK_NACADE_H

#include "../radiocommunication/radiocommunication.h"
#include "../database/firebaseadapter.h"

class NetworkFacade { 
  private:
    IDatabase *db;
    RadioCommunication *radio;
   
  public:
    void setupRadio();
    NetworkFacade(const uint64_t addrMe, const uint64_t addrOther);
    ~NetworkFacade();
    void handleNetwork(); 
};

#endif  // NETWORK_fACADE_H 
