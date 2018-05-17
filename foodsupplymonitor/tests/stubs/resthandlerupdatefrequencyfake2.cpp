#include "resthandlerupdatefrequencyfake2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RESTHandlerUpdateFrequencyFake2::executeRequest(const char* req, char* reply) {
  char src[] = "{\"updateFrequency\": 45}";
  strcpy(reply, src);
}
