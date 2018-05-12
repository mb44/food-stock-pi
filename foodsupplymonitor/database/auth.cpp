#include "auth.h"
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Auth::Auth() {
}

char * Auth::signInWithEmailAndPassword(FirebaseConfig cfg) {
  FILE *fpipe;

  string tmp = "curl https://www.googleapis.com/identitytoolkit/v3/relyingparty/verifyPassword?key="+string(cfg.apiKey)+" -H 'Content-Type: application/json' --data-binary '{\"email\":\""+string(cfg.email)+"\",\"password\":\""+string(cfg.password)+"\",\"returnSecureToken\":true}'";
 
  const char* signInCommand = tmp.c_str();
  char msg[2048];

  if (0 == (fpipe = (FILE*)popen(signInCommand, "r"))) {
    perror("popen() failed");
    exit(EXIT_FAILURE);
  }

  int i = 0;
  char c = 0;
  while (fread(&c, sizeof c, 1, fpipe)) {
    msg[i++] = c;
    //printf("%c", c);
  }

  cJSON *root = cJSON_Parse(msg);

  cJSON *reply =  cJSON_GetObjectItemCaseSensitive(root, "idToken");

  if (reply == NULL) {
    perror("FAIL: could not retrieve authentication key. Exiting...\n");
    exit(EXIT_FAILURE);
  }

  printf("Firebase auth key:\n %s\n\n", reply->valuestring);

  pclose(fpipe);

  char *res = cJSON_Print(reply);

  cJSON_Delete(root);

  return res;
}
