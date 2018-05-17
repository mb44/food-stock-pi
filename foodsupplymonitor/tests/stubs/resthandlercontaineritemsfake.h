#ifndef REST_HANDLER_CONTAINER_ITEMS_FAKE_H
#define REST_HANDLER_CONTAINER_ITEMS_FAKE_H

#include "../../database/iresthandler.h"

class RESTHandlerContainerItemsFake : public IRESTHandler {
  public:
    void executeRequest(const char *req, char *reply) override;
};

#endif // REST_HANDLER_CONTAINER_ITEMS_FAKE_H
