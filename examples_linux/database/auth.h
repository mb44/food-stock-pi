#ifndef _AUTH_H
#define _AUTH_H

#include <iostream>
#include <string>
#include "config.h"
#include "cjson.h"

class Auth {
  private:
    FirebaseConfig cfg;
  public:
    Auth(FirebaseConfig config);
    ~Auth() { std::cout << "Auth destructed" << std::endl; };
    char * signInWithEmailAndPassword();
};

#endif
