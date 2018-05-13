#include "resthandler.h"
#include <stdio.h>
#include <stdlib.h>

void RESTHandler::executeRequest(const char* req, char* reply) {
  FILE *fpipe;

  if (0 == (fpipe = (FILE*)popen(req, "r"))) {
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
