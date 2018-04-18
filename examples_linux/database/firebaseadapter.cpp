#include "firebaseadapter.h"
#include <string>
#include <iostream>


//class FirebaseAdapter;

using namespace std;

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
