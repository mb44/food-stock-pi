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

char * Auth::signInWithEmailAndPassword(FirebaseConfig cfg) {
  string tmp = "curl https://www.googleapis.com/identitytoolkit/v3/relyingparty/verifyPassword?key="+string(cfg.apiKey)+" -H 'Content-Type: application/json' --data-binary '{\"email\":\""+string(cfg.email)+"\",\"password\":\""+string(cfg.password)+"\",\"returnSecureToken\":true}'";
 
  const char* signInCommand = tmp.c_str();
  char msg[2048];

  rest->executeRequest(signInCommand, msg);

  cJSON *root = cJSON_Parse(msg);

  cJSON *reply =  cJSON_GetObjectItemCaseSensitive(root, "idToken");

  if (reply == NULL) {
    perror("FAIL: could not retrieve authentication key. Exiting...\n");
    exit(EXIT_FAILURE);
  }

  printf("Firebase auth key:\n %s\n\n", reply->valuestring);

  char *res = cJSON_Print(reply);

  cJSON_Delete(root);

  return res;
}
