#include "firebaseadapter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <cmath>

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

int FirebaseAdapter::containerItemExists(int containerId, int *exists) {
  string cmd = "curl 'https://"+string(cfg.projectId)+".firebaseio.com/containers.json?auth="+authToken+"&shallow=true'";

  char msg[FIREBASE_REPLY_MAX];

  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);
  cJSON *container = cJSON_GetArrayItem(reply, containerId+1);

  // Check for a true value at the given key
  int containerIdExists = cJSON_IsTrue(container);

  if (containerIdExists) {
    *exists = CONTAINER_ID_EXISTS;
  } else {
    *exists = CONTAINER_ID_NOT_EXISTS;
  }

  //cJSON_Delete(container);
  cJSON_Delete(reply);
  return 0;
}

int FirebaseAdapter::createContainerItem(int containerId) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "currentAmount", 0);
  cJSON_AddNumberToObject(json, "emptyContainerWeight", 0);
  cJSON_AddNumberToObject(json, "maxCapacity", 0);
  cJSON_AddStringToObject(json, "containerState", "currentAmount");
  cJSON_AddStringToObject(json, "foodName", "-");
  cJSON_AddNumberToObject(json, "updateFrequency", 30);

  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PUT -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  //cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;
  //delete reply;
  
  return 0;
}

int FirebaseAdapter::deleteContainerItem(int containerId) {
  string cmd = "curl -X DELETE 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  //cJSON *reply = cJSON_Parse(msg);
  //delete reply;

  return 0;
}

int FirebaseAdapter::setCurrentAmount(int containerId, float measurement) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, CURRENT_AMOUNT, measurement);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  printf("REQ: %s\n", cmd.c_str());
  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  //cJSON *reply = cJSON_Parse(msg);
  //delete reply;

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return 0;

}

int FirebaseAdapter::setEmptyContainerWeight(int containerId, float emptyContainerWeight) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, EMPTY_CONTAINER_WEIGHT, emptyContainerWeight);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  // cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return 0;

}

int FirebaseAdapter::setMaximumCapacity(int containerId, float maxCapacity) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, MAXIMUM_CAPACITY, maxCapacity);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH  -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  //cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return 0;

}

int FirebaseAdapter::getContainerState(int containerId, char *state) {
  string cmd = "curl 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+"/containerState.json?auth="+authToken+"'";
  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  cJSON *reply = cJSON_Parse(msg);

  // Copy the contents of reply-valuestring (char pointer) to the state char pointer)
  memcpy(state, reply->valuestring, strlen(reply->valuestring)+1);

  cJSON_Delete(reply);

  return 0;
}

int FirebaseAdapter::setContainerState(int containerId, const char *state) {
  cJSON *json = cJSON_CreateObject();
  cJSON_AddStringToObject(json, "containerState", state);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  
  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());

  //cJSON *reply = cJSON_Parse(msg);

  // Clean up
  //cJSON_Delete(json);
  delete jsonString;

  return 0;
}

int FirebaseAdapter::getUpdateFrequency(int containerId, int *updateFrequency) {
  string cmd = "curl 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+"/updateFrequency.json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  executeCURL(msg, cmd.c_str());
  cJSON *reply = cJSON_Parse(msg);

  *updateFrequency = reply->valueint;

  cJSON_Delete(reply);
  return 0;
}
