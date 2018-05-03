#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#define AUTHTOKEN_LENGTH 945
#define MAX_CONTAINERS 1000
#define FIREBASE_REPLY_MAX 4096

#define FIREBASECONFIG_LINE_LENGTH_MAX 200
#define FIREBASECONFIG_VALUE_LENGTH_MAX 150


typedef struct {
  char projectId[FIREBASECONFIG_VALUE_LENGTH_MAX];
  char apiKey[FIREBASECONFIG_VALUE_LENGTH_MAX];
  char email[FIREBASECONFIG_VALUE_LENGTH_MAX];
  char password[FIREBASECONFIG_VALUE_LENGTH_MAX];
} FirebaseConfig;

#endif
