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
  string cmd = "curl 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  char msg[2048];

  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  return reply;
}

cJSON * FirebaseAdapter::createContainerItem() {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "currentAmount", 0);
  cJSON_AddNumberToObject(json, "emptyContainerWeight", 0);
  cJSON_AddNumberToObject(json, "maxCapacity", 0);
  cJSON_AddStringToObject(json, "containerState", "measure");
  cJSON_AddStringToObject(json, "foodName", "");
  cJSON_AddNumberToObject(json, "updateFrequency", 30);

  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X POST  -d '" + string(jsonString) + "' 'https://"+cfg.projectId+".firebaseio.com/containers.json?auth="+authToken+"'";

  char msg[2048];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return reply;
}

cJSON * FirebaseAdapter::deleteContainerItem(int containerId) {
  string cmd = "curl -X DELETE 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  char msg[2048];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  return reply;

}

cJSON * FirebaseAdapter::setMeasurement(int containerId, double measurement) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "measurement", measurement);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH  -d '" + string(jsonString) + "' 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  char msg[2048];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return reply;

}

cJSON * FirebaseAdapter::setEmptyContainerWeight(int containerId, double emptyContainerWeight) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "emptyContainerWeight", emptyContainerWeight);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH  -d '" + string(jsonString) + "' 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  char msg[2048];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return reply;

}

cJSON * FirebaseAdapter::setMaximumCapacity(int containerId, double maxCapacity) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "maxCapacity", maxCapacity);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH  -d '" + string(jsonString) + "' 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  char msg[2048];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return reply;

}

cJSON * FirebaseAdapter::getContainerState(int containerId) {
  string cmd = "curl 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+"/containerState.json?auth="+authToken+"'";
  char msg[2048];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  return reply;
}

cJSON * FirebaseAdapter::setContainerState(int containerId, const char *state) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddStringToObject(json, "containerState", state);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH  -d '" + string(jsonString) + "' 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  
  char msg[2048];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return reply;
}

cJSON * FirebaseAdapter::getUpdateFrequency(int containerId) {
  string cmd = "curl 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+"/updateFrequency.json?auth="+authToken+"'";

  char msg[2048];
  executeCURL(msg, cmd.c_str());
  cJSON *reply = cJSON_Parse(msg);

  return reply;
}
