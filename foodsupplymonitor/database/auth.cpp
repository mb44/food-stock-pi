#include "auth.h"
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "resthandler.h"

using namespace std;

Auth::Auth(IRESTHandler *rest)
: rest(rest) 
{}

uint8_t Auth::signInWithEmailAndPassword(const FirebaseConfig cfg, char *reply) {
  string tmp = "curl https://www.googleapis.com/identitytoolkit/v3/relyingparty/verifyPassword?key="+string(cfg.apiKey)+" -H 'Content-Type: application/json' --data-binary '{\"email\":\""+string(cfg.email)+"\",\"password\":\""+string(cfg.password)+"\",\"returnSecureToken\":true}'";
 
  const char* signInCommand = tmp.c_str();
  char msg[2048];

  rest->executeRequest(signInCommand, msg);

  cJSON *root = cJSON_Parse(msg);

  cJSON *dbReply =  cJSON_GetObjectItemCaseSensitive(root, "idToken");

  if (dbReply == NULL) {
    // perror("FAIL: could not retrieve authentication key. Exiting...\n");
    // exit(EXIT_FAILURE);
    return 1;
  }

  printf("Firebase auth key:\n %s\n\n", dbReply->valuestring);

  reply = cJSON_Print(dbReply);

  cJSON_Delete(root);

  return 0;
}
