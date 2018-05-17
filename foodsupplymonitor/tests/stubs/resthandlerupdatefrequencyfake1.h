#ifndef REST_HANDLER_UPDATE_FREQUENCY_FAKE1_H
#define REST_HANDLER_UPDATE_FREQUENCY_FAKE1_H

#include "../../database/iresthandler.h"

class RESTHandlerUpdateFrequencyFake1 : public IRESTHandler {
  public:
    void executeRequest(const char *req, char *reply) override;
};

#endif // REST_HANDLER_UPDATE_FREQUENCY_FAKE1_H
