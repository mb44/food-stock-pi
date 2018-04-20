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
  public:
    FirebaseAdapter();
    virtual ~FirebaseAdapter();
    cJSON * getContainerItem(int containerId) override;
    void authenticate();
    std::string createContainerItem(std::string containerItem) override;
    std::string deleteContainerItem(int containerId) override;
    std::string setMeasurement(int containerId, double measurement) override;
    std::string setEmptyContainerWeight(int containerId, double measurement) override;
    std::string setMaximumCapacity(int containerId, double maxCapacity) override;
    cJSON * getContainerState(int containerId) override;
    cJSON * setContainerState(int containerId, std::string state) override;
    cJSON * getUpdateFrequency(int containerId) override;
};

#endif // FIREBASEADAPTER_H
