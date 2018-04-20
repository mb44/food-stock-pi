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

void FirebaseAdapter::executeCURL(char *reply, const char *cmd) { 
  FILE *fpipe;

  if (0 == (fpipe = (FILE*)popen(cmd, "r"))) {
    perror("popen() failed");
    exit(1);
  }

  int i = 0;
  char c = 0;
  while (fread(&c, sizeof c, 1, fpipe)) {
    reply[i++] = c;
  }

  fclose(fpipe);
}

cJSON * FirebaseAdapter::getContainerItem(int containerId) {
  printf("Get container item auth: %s\n", authToken);
  string cmd = "curl 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  char msg[2048];

  executeCURL(msg, cmd.c_str());

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

cJSON * FirebaseAdapter::setMaximumCapacity(int containerId, double maxCapacity) {

}

cJSON * FirebaseAdapter::getContainerState(int containerId) {
  string cmd = "curl 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+"/containerState.json?auth="+authToken+"'";
  char msg[2048];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  return reply;
}

cJSON * FirebaseAdapter::setContainerState(int containerId, const char *state) {
  cJSON *data = cJSON_CreateObject();
  cJSON_AddStringToObject(data, "containerState", state);
  char *tmpData = cJSON_PrintUnformatted(data);

  string cmd = "curl -X PATCH  -d '" + string(tmpData) + "' 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  
  char msg[2048];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(data);
  delete tmpData;

  return reply;
}

cJSON * FirebaseAdapter::getUpdateFrequency(int containerId) {
  string cmd = "curl 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+"/updateFrequency.json?auth="+authToken+"'";

  char msg[2048];
  executeCURL(msg, cmd.c_str());
  cJSON *reply = cJSON_Parse(msg);

  return reply;
}
