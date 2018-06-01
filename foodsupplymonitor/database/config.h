#ifndef CONFIG_H
#define CONFIG_H

#include "dbdefines.h"

/*! \file config.h
    \brief Contains a struct with Firebase configuration details.
*/

typedef struct {
  char projectId[FIREBASECONFIG_VALUE_LENGTH_MAX];
  char apiKey[FIREBASECONFIG_VALUE_LENGTH_MAX];
  char email[FIREBASECONFIG_VALUE_LENGTH_MAX];
  char password[FIREBASECONFIG_VALUE_LENGTH_MAX];
} FirebaseConfig;

#endif
