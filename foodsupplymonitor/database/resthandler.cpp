#include "resthandler.h"
#include <stdio.h>
#include <stdlib.h>

/*! \file resthandler.cpp
    \brief Implementaion of rest handler functionality
*/

/*! \brief Method to execute an HTTP request
	\param[in]  req a char array containing the request
	\param[out] reply a char a array containg the response
*/
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
