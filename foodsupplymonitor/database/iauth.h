#ifndef IAUTH_H
#define IAUTH_H

#include <iostream>
#include <string>
#include "config.h"
#include "cjson.h"

class IAuth {
  public:
    virtual char * signInWithEmailAndPassword(FirebaseConfig config) = 0;
};

#endif // IAUTH_H
