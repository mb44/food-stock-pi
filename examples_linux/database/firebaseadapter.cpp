#include "firebaseadapter.h"
#include <string>
#include <iostream>

using namespace std;

FirebaseAdapter::FirebaseAdapter() {
  //cout << "Constructor called" << endl;
  FirebaseConfig cfg;
  //cfg.projectId = "foodwastereduction-6ca48";
  //cfg.apiKey = "AIzaSyBxlo2I0gI-2c5nb3w9feXabKInEvVotj8";
  //cfg.email = "mortenbeuchert@gmail.com";
  //cfg.password = "123456";
  auth = new Auth(cfg);

  authToken = auth->signInWithEmailAndPassword();
  cout << "FirebaseAdapter: " << authToken->valuestring << endl; 
}

FirebaseAdapter::~FirebaseAdapter() {
  // delete auth;
  // free authToken;
  // delete jsonReply;
}

cJSON * FirebaseAdapter::getContainerItem(int containerId) {
  cout << "Get containerItem" << endl;
  string tmp = "curl 'https://"+cfg.projectId+".firebaseio.com/containers/"+to_string(containerId)+".json?auth="+authToken->valuestring+"'";

  cout << endl << "Tmp: " << tmp << endl;

  FILE *fpipe;

  const char* getContainerItemCmd = tmp.c_str();
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
