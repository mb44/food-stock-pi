#ifndef AUTHSTUB_H
#define AUTHSTUB_H

#include "../database/iauth.h"

class AuthStub : public IAuth {
  public:
    AuthStub();
    ~AuthStub() {};
    char * signInWithEmailAndPassword(FirebaseConfig config) override;
};

#endif // AUTHSTUB_H
