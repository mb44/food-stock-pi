#ifndef REST_HANDLER_UPDATE_FREQUENCY_FAKE2_H
#define REST_HANDLER_UPDATE_FREQUENCY_FAKE2_H

#include "../../database/iresthandler.h"

class RESTHandlerUpdateFrequencyFake2 : public IRESTHandler {
  public:
    void executeRequest(const char *req, char *reply) override;
};

#endif // REST_HANDLER_UPDATE_FREQUENCY_FAKE2_H
