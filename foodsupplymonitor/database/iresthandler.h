#ifndef IREST_HANDLER_H
#define IREST_HANDLER_H

class IRESTHandler {
  public:
    virtual ~IRESTHandler() {}
    virtual void executeRequest(const char *req, char *reply) = 0;
};

#endif // IREST_HANDLER_H
