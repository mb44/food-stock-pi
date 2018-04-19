#include "firebaseadapter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

FirebaseAdapter::FirebaseAdapter() {
  auth = new Auth(); //new Auth(cfg);

  char *reply = auth->signInWithEmailAndPassword(cfg);

  authToken = (char *)malloc(AUTHTOKEN_LENGTH+1);


  memcpy(authToken, &reply[1], AUTHTOKEN_LENGTH+1);
  free(reply); 
  authToken[AUTHTOKEN_LENGTH] = '\0';
  

  printf("FirebaseAdapter: %s\n", authToken);
}

FirebaseAdapter::~FirebaseAdapter() {
  //free(auth);
  // free authToken;
  // delete jsonReply;
}

cJSON * FirebaseAdapter::getContainerItem(int containerId) {
  printf("Get container item auth: %s\n", authToken);
  string tmp = "curl 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  //printf("FirebaseAdapter url: %s\n", tmp);

  FILE *fpipe;

  const char* getContainerItemCmd = tmp.c_str();
  printf("GetContainer url: %s\n", getContainerItemCmd);  

  char msg[2048];

  if (0 == (fpipe = (FILE*)popen(getContainerItemCmd, "r"))) {
    perror("popen() failed");
    exit(1);
  }

  int i = 0;
  char c = 0;
  while (fread(&c, sizeof c, 1, fpipe)) {
    msg[i++] = c;
  }

  cJSON *reply = cJSON_Parse(msg);

  return reply;
}

string FirebaseAdapter::createContainerItem(string containerItem) {
  return "";
}

string FirebaseAdapter::deleteContainerItem(int containerId) {
  return "";
}

string FirebaseAdapter::setMeasurement(int containerId, double measurement) {
  return "";
}

string FirebaseAdapter::setEmptyContainerWeight(int containerId, double measurement) {
  return "";
}

string FirebaseAdapter::setMaximumCapacity(int containerId, double maxCapacity) {
  return "";
}

string FirebaseAdapter::getContainerState(int containerId) {
  return "";
}

string FirebaseAdapter::setContainerState(int containerid, string state) {
  return "";
}

string FirebaseAdapter::getUpdateFrequency(int containerId) {
  return "";
}
