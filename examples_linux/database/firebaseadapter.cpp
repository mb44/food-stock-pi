#include "firebaseadapter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

FirebaseAdapter::FirebaseAdapter() {
  auth = new Auth(); //new Auth(cfg);

  authenticate();
  /*
  char *reply = auth->signInWithEmailAndPassword(cfg);

  authToken = (char *)malloc(AUTHTOKEN_LENGTH+1);

  memcpy(authToken, &reply[1], AUTHTOKEN_LENGTH+1);
  free(reply); 
  authToken[AUTHTOKEN_LENGTH] = '\0';
  

  printf("FirebaseAdapter: %s\n", authToken);
  */
}

FirebaseAdapter::~FirebaseAdapter() {
  //free(auth);
  // free authToken;
  // delete jsonReply;
}

void FirebaseAdapter::authenticate() {
  char *reply = auth->signInWithEmailAndPassword(cfg);

  ///if (authToken != NULL) {
    //free(authToken);
  //}

  //authToken = (char *)malloc(AUTHTOKEN_LENGTH+1);
  
  memcpy(authToken, &reply[1], AUTHTOKEN_LENGTH+1);
  free(reply);
  authToken[AUTHTOKEN_LENGTH] = '\0';
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

cJSON * FirebaseAdapter::getContainerState(int containerId) {
  string tmp = "curl 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+"/containerState.json?auth="+authToken+"'";

  FILE *fpipe;

  const char* getContainerStateCmd = tmp.c_str();

  char msg[2048];

  if (0 == (fpipe = (FILE*)popen(getContainerStateCmd, "r"))) {
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

cJSON * FirebaseAdapter::setContainerState(int containerId, string state) {
  //cJSON *num = cJSON_CreateString(state.c_str());

  cJSON *data = cJSON_CreateObject();

  cJSON_AddStringToObject(data, "containerState", state.c_str());

  char *tempData = cJSON_PrintUnformatted(data);

  string tmp = "curl -X PATCH  -d '" + string(tempData) + "' 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  cout << endl << "SetState url: " << tmp << endl;

  cout << "STRING: " << tmp << endl;

  FILE *fpipe;

  const char* setContainerStateCmd = tmp.c_str();

  char msg[2048];

  if (0 == (fpipe = (FILE*)popen(setContainerStateCmd, "r"))) {
    perror("popen() failed");
    exit(1);
  }

  cJSON_Delete(data);

  int i = 0;
  char c = 0;
  while (fread(&c, sizeof c, 1, fpipe)) {
    msg[i++] = c;
  }

  cJSON *reply = cJSON_Parse(msg);

  return reply;
}

cJSON * FirebaseAdapter::getUpdateFrequency(int containerId) {
  string tmp = "curl 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+"/updateFrequency.json?auth="+authToken+"'";

  //printf("FirebaseAdapter url: %s\n", tmp);

  FILE *fpipe;

  const char* getUpdateFrequencyCmd = tmp.c_str();

  char msg[2048];

  if (0 == (fpipe = (FILE*)popen(getUpdateFrequencyCmd, "r"))) {
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
