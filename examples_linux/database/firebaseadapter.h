#ifndef DATABASE_H
#define DATABASE_H

#include "idatabase.h"
#include "auth.h"
#include <string>
#include <iostream>

class FirebaseAdapter : public IDatabase {
  private:
    FirebaseConfig cfg;
    Auth *auth;
    std::string httpHeader;
    //char *authToken;
    char authToken[946];
    cJSON *jsonReply;
    void executeCURL(char *reply, const char *cmd);
    int getUniqueContainerId();
  public:
    FirebaseAdapter();
    virtual ~FirebaseAdapter();
    void authenticate();
    cJSON * getContainerItem(int containerId) override;
    cJSON * createContainerItem() override;
    cJSON * deleteContainerItem(int containerId) override;
    cJSON * setMeasurement(int containerId, double measurement) override;
    cJSON * setEmptyContainerWeight(int containerId, double measurement) override;
    cJSON * setMaximumCapacity(int containerId, double maxCapacity) override;
    cJSON * getContainerState(int containerId) override;
    cJSON * setContainerState(int containerId, const char *state) override;
    cJSON * getUpdateFrequency(int containerId) override;
};

#endif // FIREBASEADAPTER_H
