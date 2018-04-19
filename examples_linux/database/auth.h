#ifndef _AUTH_H
#define _AUTH_H

#include <iostream>
#include <string>
#include "globals.h"
#include "cjson.h"

class Auth {
  private:
    FirebaseConfig config;
  public:
    Auth(FirebaseConfig cfg);
    ~Auth() { std::cout << "Auth destructed" << std::endl; };
    cJSON * signInWithEmailAndPassword();
};

#endif
