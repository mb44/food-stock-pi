#ifndef _AUTH_H
#define _AUTH_H

#include <iostream>
#include <string>

typedef struct {
  std::string projectId = "foodwastereduction-6ca48";
  std::string apiKey = "AIzaSyBxlo2I0gI-2c5nb3w9feXabKInEvVotj8";
  std::string email = "mortenbeuchert@gmail.com";
  std::string password = "123456";
} FirebaseConfig;

class Auth {
  private:
    FirebaseConfig config;
  public:
    Auth(FirebaseConfig cfg);
    ~Auth() { std::cout << "Auth destructed" << std::endl; };
    std::string signInWithEmailAndPassword();
};

#endif
