#include "auth.h"
#include "cjson.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Auth::Auth(FirebaseConfig cfg) {
  config = cfg;
  signInWithEmailAndPassword();
}

string Auth::signInWithEmailAndPassword() {
  cout << "sign in with email and password" << endl;
  FILE *fpipe;

  string temp = "curl https://www.googleapis.com/identitytoolkit/v3/relyingparty/verifyPassword?key="+config.apiKey+" -H 'Content-Type: application/json' --data-binary '{\"email\":\""+config.email+"\",\"password\":\""+config.password+"\",\"returnSecureToken\":true}'";
   
  const char* signInCommand = temp.c_str();
  char c = 0;  
  char msg[2048];


  if (0 == (fpipe = (FILE*)popen(signInCommand, "r"))) {
    perror("popen() failed");
    exit(1);
  }

  int i = 0;
  while(fread(&c, sizeof c, 1, fpipe)) {
    msg[i++] = c;
    //printf("%c", c);
  }

  cJSON *root = cJSON_Parse(msg);
  //cJSON *foodTypes = cJSON_GetArrayItem(0);

  //char* response = cJSON_Print(root);
  
  const cJSON *idTokenStr =  cJSON_GetObjectItemCaseSensitive(root, "idToken");
  printf("%s", idTokenStr->valuestring);

  pclose(fpipe);

  cout << "Authing" << endl;
  return "";
}
