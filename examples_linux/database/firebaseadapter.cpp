#include "firebaseadapter.h"
#include <string>
#include <iostream>


//class FirebaseAdapter;

using namespace std;

FirebaseAdapter::FirebaseAdapter() {
  //cout << "Constructor called" << endl;
  FirebaseConfig cfg;
  cfg.projectId = "foodwastereduction-6ca48";
  cfg.apiKey = "AIzaSyBxlo2I0gI-2c5nb3w9feXabKInEvVotj8";
  cfg.email = "mortenbeuchert@gmail.com";
  cfg.password = "123456";

  auth = new Auth(cfg);
}

FirebaseAdapter::~FirebaseAdapter() {
  //cout << "FirebaseAdapter destructed" << endl;
  delete auth;
}

string FirebaseAdapter::getContainerItem(int containerId) {
  cout << "Firebase test" << endl;
  return "abc";
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
