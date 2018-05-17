#include "resthandlerupdatefrequencyfake1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RESTHandlerUpdateFrequencyFake1::executeRequest(const char* req, char* reply) {
  char dbReply[] = "-5";
  strcpy(reply, dbReply);
}
