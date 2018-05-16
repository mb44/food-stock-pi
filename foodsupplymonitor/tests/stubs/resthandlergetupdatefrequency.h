#ifndef REST_HANDLER_GET_UPDATE_FREQUENCY_STUB_H
#define REST_HANDLER_GET_UPDATE_FREQUENCY_STUB_H

#include "iresthandler.h"

class RESTHandlerGetUpdateFrequencyStub : public IRESTHandler {
  public:
    void executeRequest(const char *req, char *reply) override;
};

#endif // REST_HANDLER_GET_UPDATE_FREQUENCY_STUB_H
