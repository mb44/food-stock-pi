#include "firebaseadapter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

FirebaseAdapter::FirebaseAdapter(char *firebaseConfig) {
  parseConfig(firebaseConfig);
  auth = new Auth();

  authenticate();
}

FirebaseAdapter::~FirebaseAdapter() {
  delete auth;
}

void FirebaseAdapter::authenticate() {
  char *reply = auth->signInWithEmailAndPassword(cfg);

  /*
  if (authToken != NULL) {
    free(authToken);
  }
  */

  memcpy(authToken, &reply[1], AUTHTOKEN_LENGTH+1);
  free(reply);
  authToken[AUTHTOKEN_LENGTH] = '\0';
}

void FirebaseAdapter::parseConfig(char *firebaseConfig) {
  char line[FIREBASECONFIG_LINE_LENGTH_MAX];

  FILE *fp;

  if ((fp = fopen(firebaseConfig, "r")) == NULL) {
    perror("Error opening file\n");
    exit(EXIT_FAILURE);
  }

  fgets(line, FIREBASECONFIG_LINE_LENGTH_MAX, fp);
  sscanf(line, "projectId: %s", cfg.projectId);

  fgets(line, FIREBASECONFIG_LINE_LENGTH_MAX, fp);
  sscanf(line, "apiKey: %s", cfg.apiKey);

  fgets(line, FIREBASECONFIG_LINE_LENGTH_MAX, fp);
  sscanf(line, "email: %s", cfg.email);

  fgets(line, FIREBASECONFIG_LINE_LENGTH_MAX, fp);
  sscanf(line, "password: %s", cfg.password);

  fclose(fp);
}

void FirebaseAdapter::executeCURL(char *reply, const char *cmd) {
  FILE *fpipe;

  if (0 == (fpipe = (FILE*)popen(cmd, "r"))) {
    perror("popen() failed");
    exit(EXIT_FAILURE);
  }

  int i = 0;
  char c = 0;
  while (fread(&c, sizeof c, 1, fpipe)) {
    reply[i++] = c;
  }

  fclose(fpipe);
}

int FirebaseAdapter::getUniqueContainerId() {
string cmd = "curl 'https://"+string(cfg.projectId)+".firebaseio.com/containers.json?auth="+authToken+"&shallow=true'";
  char msg[FIREBASE_REPLY_MAX];

  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  int newContainerId = cJSON_GetArraySize(reply);


  printf("New Container Id: %d\n", newContainerId);
  /*
  int newContainerId = 0;
  cJSON *child;
  int i;
  for (i=0; i<MAX_CONTAINERS; i++) {
    child = cJSON_GetArrayItem(reply, i);
    if (child == NULL) {
     // Found it!
      newContainerId = i+1;
      break;
    }
  }
  */

  cJSON_Delete(reply);
  return newContainerId;
}

cJSON * FirebaseAdapter::getContainerItem(int containerId) {
  string cmd = "curl 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  char msg[2048];

  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  return reply;
}

cJSON * FirebaseAdapter::createContainerItem() {
  int newContainerId = getUniqueContainerId();

  //cout << "create container id: " << number << endl;

  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "currentAmount", 0);
  cJSON_AddNumberToObject(json, "emptyContainerWeight", 0);
  cJSON_AddNumberToObject(json, "maxCapacity", 0);
  cJSON_AddStringToObject(json, "containerState", "measure");
  cJSON_AddStringToObject(json, "foodName", "-");
  cJSON_AddNumberToObject(json, "updateFrequency", 30);

  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PUT -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(newContainerId)+".json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return reply;
}

cJSON * FirebaseAdapter::deleteContainerItem(int containerId) {
  string cmd = "curl -X DELETE 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  return reply;

}

cJSON * FirebaseAdapter::setMeasurement(int containerId, float measurement) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "measurement", measurement);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return reply;

}

cJSON * FirebaseAdapter::setEmptyContainerWeight(int containerId, float emptyContainerWeight) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "emptyContainerWeight", emptyContainerWeight);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return reply;

}

cJSON * FirebaseAdapter::setMaximumCapacity(int containerId, float maxCapacity) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "maxCapacity", maxCapacity);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH  -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return reply;

}

cJSON * FirebaseAdapter::getContainerState(int containerId) {
  string cmd = "curl 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+"/containerState.json?auth="+authToken+"'";
  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  return reply;
}

cJSON * FirebaseAdapter::setContainerState(int containerId, const char *state) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddStringToObject(json, "containerState", state);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  
  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return reply;
}

cJSON * FirebaseAdapter::getUpdateFrequency(int containerId) {
  string cmd = "curl 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+"/updateFrequency.json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());
  cJSON *reply = cJSON_Parse(msg);

  return reply;
}
