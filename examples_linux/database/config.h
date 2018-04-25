#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#define AUTHTOKEN_LENGTH 945
#define MAX_CONTAINERS 1000
#define FIREBASE_REPLY_MAX 4096

#define FIREBASECONFIG_LINE_LENGTH_MAX 200
#define FIREBASECONFIG_VALUE_LENGTH_MAX 150


typedef struct {
  char projectId[FIREBASECONFIG_VALUE_LENGTH_MAX]; // ="foodwastereduction-6ca48";
  char apiKey[FIREBASECONFIG_VALUE_LENGTH_MAX]; // = "AIzaSyBxlo2I0gI-2c5nb3w9feXabKInEvVotj8";
  char email[FIREBASECONFIG_VALUE_LENGTH_MAX]; // = "mortenbeuchert@gmail.com";
  char password[FIREBASECONFIG_VALUE_LENGTH_MAX]; // = "123456";
} FirebaseConfig;

#endif
