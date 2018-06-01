#ifndef IAUTH_H
#define IAUTH_H

#include <iostream>
#include <string>
#include "config.h"
#include "cjson.h"

/*! \file iauth.h
    \brief Interface for user authentiation with email and password
*/

class IAuth {
  public:
    virtual ~IAuth() {}
    virtual uint8_t signInWithEmailAndPassword(const FirebaseConfig config, char *authToken) = 0;
};

#endif // IAUTH_H
