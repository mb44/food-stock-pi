#ifndef _NETWORK_FACADE_H
#define _NETWORK_NACADE_H

#include "../radiocommunication/rf24adapter.h"
#include "../database/firebaseadapter.h"

class NetworkFacade { 
  private:
    IDatabase *db;
    IRadio *radio;
   
  public:
    void setupRadio();
    NetworkFacade(const uint64_t pipes[2]);
    ~NetworkFacade();
    void handleNetwork(); 
};

#endif  // NETWORK_fACADE_H 
