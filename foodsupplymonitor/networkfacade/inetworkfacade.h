#ifndef INETWORK_FACADE_H
#define INETWORK_NACADE_H

#include "../radio/rf24adapter.h"
#include "../database/firebaseadapter.h"

/*! \file inetworkfacade.h
    \brief Interface for NetworkFacade.
*/
class INetworkFacade { 
   
  public:
    virtual ~INetworkFacade() {}
    virtual void handleNetwork() = 0; 
};

#endif  // INETWORK_FACADE_H 
