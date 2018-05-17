#include "resthandlercontaineritemsfake.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RESTHandlerContainerItemsFake::executeRequest(const char* req, char* reply) {
  char dbReply[] = "{\"0\": true, \"1\": true, \"2\": true, \"4\": true, \"5\": true}";
  strcpy(reply, dbReply);
}
