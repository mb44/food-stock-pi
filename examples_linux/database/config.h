#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#define AUTHTOKEN_LENGTH 945

typedef struct {
  std::string projectId ="foodwastereduction-6ca48";
  std::string apiKey = "AIzaSyBxlo2I0gI-2c5nb3w9feXabKInEvVotj8";
  std::string email = "mortenbeuchert@gmail.com";
  std::string password = "123456";
} FirebaseConfig;

#endif
