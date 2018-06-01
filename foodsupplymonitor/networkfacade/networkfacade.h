#ifndef NETWORK_FACADE_H
#define NETWORK_NACADE_H

#include "inetworkfacade.h"

/*! \file networkfacade.h
    \brief Implementation of NetworkFacade.
*/

class NetworkFacade : public INetworkFacade { 
  private:
    IRadio *radio;
    IDatabase *db;
   
  public:
    NetworkFacade(IRadio *r, IDatabase *d);
    virtual ~NetworkFacade();
    void handleNetwork() override; 
};

#endif  // NETWORK_FACADE_H 
