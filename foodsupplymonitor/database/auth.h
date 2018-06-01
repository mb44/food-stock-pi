#ifndef AUTH_H
#define AUTH_H

#include "iauth.h"
#include "iresthandler.h"

/*! \file auth.h
    \brief Implementation for user authentiation with email and password
*/
class Auth : public IAuth {
  private:
  
    IRESTHandler *rest;
  public:
    Auth(IRESTHandler *rest);
    ~Auth() {}
    uint8_t signInWithEmailAndPassword(const FirebaseConfig config, char *authToken) override;
};

#endif
