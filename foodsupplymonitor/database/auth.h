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
    char * signInWithEmailAndPassword(FirebaseConfig config) override;
};

#endif
