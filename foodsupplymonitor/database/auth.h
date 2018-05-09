#ifndef AUTH_H
#define AUTH_H

#include "iauth.h"

class Auth : public IAuth {
  public:
    Auth();
    ~Auth() { std::cout << "Auth destructed" << std::endl; };
    char * signInWithEmailAndPassword(FirebaseConfig config) override;
};

#endif
