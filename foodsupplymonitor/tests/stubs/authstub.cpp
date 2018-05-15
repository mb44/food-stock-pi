#include "authstub.h"
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

AuthStub::AuthStub() {
}

char * AuthStub::signInWithEmailAndPassword(FirebaseConfig cfg) {
  char *res = malloc(946 * sizeof(char));
  res = "abcfirebase";

  return res;
}
