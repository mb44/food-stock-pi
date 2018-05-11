#ifndef NETWORK_FACADE_H
#define NETWORK_NACADE_H

#include "inetworkfacade.h"


class NetworkFacade : public INetworkFacade { 
  private:
    IDatabase *db;
    IRadio *radio;
    void setupRadio();
   
  public:
    NetworkFacade(IRadio *r, IDatabase *d);
    virtual ~NetworkFacade();
    void handleNetwork() override; 
};

#endif  // NETWORK_FACADE_H 
