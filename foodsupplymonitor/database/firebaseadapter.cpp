#include "firebaseadapter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

/*! \file firebaseadapter.cpp
    \brief Implementation for database operations.
*/

/*! \brief Constructor.
	\param[in] auth pointer to auth interface.
	\param[in] rest pointer to rest interface.
	\param[in] configPath string containing the file path to Firebase config file.
*/
FirebaseAdapter::FirebaseAdapter(IAuth *auth, IRESTHandler *rest, const char *configPath) 
: auth(auth),
  rest(rest) ,
  configPath(configPath)
{}

/*! \brief Destructor
*/
FirebaseAdapter::~FirebaseAdapter() {
}

/*! \brief Method to authenticate user.
*/
uint8_t FirebaseAdapter::authenticate() {
  parseConfig();

  uint8_t result = auth->signInWithEmailAndPassword(cfg, authToken);

  if (result) {
    return 1;
  }

  return 0;
}

/*! \brief Method to parse the Firebase configuration file.
*/
void FirebaseAdapter::parseConfig() {
  char line[FIREBASECONFIG_LINE_LENGTH_MAX];

  FILE *fp;

  if ((fp = fopen(configPath, "r")) == NULL) {
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

/*! \brief Method to sign in user.
	\param[in] containerId The container ID.
	\param[out] exists contains 0 if container exists true and 1 otherwise.
	\returns 0 on success and 1 otherwise.
*/
uint8_t FirebaseAdapter::containerItemExists(int containerId, uint8_t *exists) {
  if (containerId<0 || containerId>MAX_CONTAINERS) {
    return 1;
  }

  string cmd = "curl 'https://"+string(cfg.projectId)+".firebaseio.com/containers.json?auth="+authToken+"&shallow=true'";

  char msg[FIREBASE_REPLY_MAX];

  rest->executeRequest(cmd.c_str(), msg);

  cJSON *reply = cJSON_Parse(msg);

  if (reply==NULL) {
    return 1;
  }

  cJSON *container = cJSON_GetArrayItem(reply, containerId+1);

  // Check for truth value at the given key
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

/*! \brief Method to create a container item.
	\param[in] containerId The container ID.
	\returns 0 on success and 1 otherwise.
*/
uint8_t FirebaseAdapter::createContainerItem(int containerId) {
  if (containerId<0 || containerId>MAX_CONTAINERS) {
    return 1;
  }

  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "currentAmount", 0);
  cJSON_AddNumberToObject(json, "emptyContainerWeight", 0);
  cJSON_AddNumberToObject(json, "maxCapacity", 0);
  cJSON_AddStringToObject(json, "containerState", "currentAmount");
  cJSON_AddStringToObject(json, "foodName", "-");
  cJSON_AddNumberToObject(json, "updateFrequency", 30);

  char *jsonString = cJSON_PrintUnformatted(json);

  if (jsonString == NULL) {
    return 1;
  }

  string cmd = "curl -X PUT -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  rest->executeRequest(cmd.c_str(), msg);

  //cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;
  //delete reply;
  
  return 0;
}

/*! \brief Method to set current amount.
	\param[in] containerId The container ID.
	\param[in] currentAmount The current amount.
	\returns 0 on success and 1 otherwise.
*/
uint8_t FirebaseAdapter::setCurrentAmount(int containerId, float currentAmount) {
  if (containerId<0 || containerId>MAX_CONTAINERS) {
    return 1;
  } else if (currentAmount<0) {
    return 1;
  }

  cJSON *json = cJSON_CreateObject();
  float currentAmountRounded = round(currentAmount*1000.0)/1000.0;
  cJSON_AddNumberToObject(json, CURRENT_AMOUNT, currentAmountRounded);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  char msg[FIREBASE_REPLY_MAX];
  rest->executeRequest(cmd.c_str(), msg);

  //cJSON *reply = cJSON_Parse(msg);
  //delete reply;

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return 0;

}

/*! \brief Method to set empty container weight.
	\param[in] containerId The container ID.
	\param[in] emptyContainerWeight The empty container weight.
	\returns 0 on success and 1 otherwise.
*/
uint8_t FirebaseAdapter::setEmptyContainerWeight(int containerId, float emptyContainerWeight) {
  if (containerId<0 || containerId>MAX_CONTAINERS) {
    return 1;
  } else if (emptyContainerWeight<=0) {
    return 1;
  }

  cJSON *json = cJSON_CreateObject();
  float emptyContainerWeightRounded = round(emptyContainerWeight*1000.0)/1000.0;
  cJSON_AddNumberToObject(json, EMPTY_CONTAINER_WEIGHT, emptyContainerWeightRounded);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  rest->executeRequest(cmd.c_str(), msg);

  // cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return 0;

}

/*! \brief Method to set maximum capacity.
	\param[in] containerId The container ID.
	\param[in] maximumCapacity The maximum capacity.
	\returns 0 on success and 1 otherwise.
*/
uint8_t FirebaseAdapter::setMaximumCapacity(int containerId, float maximumCapacity) {
  if (containerId<0 || containerId>MAX_CONTAINERS) {
    return 1;
  } else if (maximumCapacity<=0) {
    return 1;
  }

  cJSON *json = cJSON_CreateObject();
  float maximumCapacityRounded = round(maximumCapacity*1000.0)/1000.0;
  cJSON_AddNumberToObject(json, MAXIMUM_CAPACITY, maximumCapacityRounded);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH  -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  rest->executeRequest(cmd.c_str(), msg);

  //cJSON *reply = cJSON_Parse(msg);

  // Clean up
  cJSON_Delete(json);
  delete jsonString;

  return 0;

}

/*! \brief Method to get the container state.
	\param[in] containerId The container ID.
	\param[out] state The current container state.
	\returns 0 on success and 1 otherwise.
*/
uint8_t FirebaseAdapter::getContainerState(int containerId, char *state) {
  if (containerId<0 || containerId>MAX_CONTAINERS) {
    return 1;
  }

  string cmd = "curl 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+"/containerState.json?auth="+authToken+"'";
  char msg[FIREBASE_REPLY_MAX];
  rest->executeRequest(cmd.c_str(), msg);

  cJSON *reply = cJSON_Parse(msg);

  if (reply==NULL) {
    return 1;
  }

  // Copy the contents of reply->valuestring (char pointer) to the state char pointer
  memcpy(state, reply->valuestring, strlen(reply->valuestring)+1);

  cJSON_Delete(reply);

  return 0;
}

/*! \brief Method to set container state.
	\param[in] containerId The container ID.
	\param[in] state A char pointer containing a string of the state.
	\returns 0 on success and 1 otherwise.
*/
uint8_t FirebaseAdapter::setContainerState(int containerId, const char *state) {
  if (containerId<0 || containerId>MAX_CONTAINERS) {
    return 1;
  }
  
  cJSON *json = cJSON_CreateObject();
  cJSON_AddStringToObject(json, "containerState", state);
  char *jsonString = cJSON_PrintUnformatted(json);

  string cmd = "curl -X PATCH -d '" + string(jsonString) + "' 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken+"'";
  
  char msg[FIREBASE_REPLY_MAX];
  rest->executeRequest(cmd.c_str(), msg);

  //cJSON *reply = cJSON_Parse(msg);

  // Clean up
  //cJSON_Delete(json);
  delete jsonString;

  return 0;
}

/*! \brief Method to get the update frequency.
	\param[in] containerId The container ID.
	\param[out] updateFrequency The update frequency of the container.
	\returns 0 on success and 1 otherwise.
*/
uint8_t FirebaseAdapter::getUpdateFrequency(int containerId, int *updateFrequency) {
  if (containerId<0 || containerId>MAX_CONTAINERS) {
    return 1;
  }

  string cmd = "curl 'https://"+string(cfg.projectId)+".firebaseio.com/containers/"+to_string(containerId)+"/updateFrequency.json?auth="+authToken+"'";

  char msg[FIREBASE_REPLY_MAX];
  rest->executeRequest(cmd.c_str(), msg);

  cJSON *reply = cJSON_Parse(msg);

  *updateFrequency = reply->valueint;

  if (*updateFrequency<=0) {
    return 1;
  }

  cJSON_Delete(reply);
  return 0;
}
