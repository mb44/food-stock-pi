#ifndef AUTH_H
#define AUTH_H

#include "iauth.h"
#include "iresthandler.h"

class Auth : public IAuth {
  private:
  
    IRESTHandler *rest;
  public:
    Auth(IRESTHandler *rest);
    ~Auth() {}
    uint8_t signInWithEmailAndPassword(const FirebaseConfig config, char *reply) override;
};

#endif
