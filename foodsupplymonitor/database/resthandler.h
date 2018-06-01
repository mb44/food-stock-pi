#ifndef REST_HANDLER_H
#define REST_HANDLER_H

#include "iresthandler.h"

/*! \file resthandler.h
    \brief Implementaion of rest handler functionality
*/
class RESTHandler : public IRESTHandler {
  public:
    void executeRequest(const char *req, char *reply) override;
};

#endif // REST_HANDLER_H
