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
    cJSON *authToken;
    cJSON *jsonReply;
  public:
    FirebaseAdapter();
    virtual ~FirebaseAdapter();
    cJSON * getContainerItem(int containerId) override;
    std::string createContainerItem(std::string containerItem) override;
    std::string deleteContainerItem(int containerId) override;
    std::string setMeasurement(int containerId, double measurement) override;
    std::string setEmptyContainerWeight(int containerId, double measurement) override;
    std::string setMaximumCapacity(int containerId, double maxCapacity) override;
    std::string getContainerState(int containerId) override;
    std::string setContainerState(int containerId, std::string state) override;
    std::string getUpdateFrequency(int containerId) override;
};

#endif // FIREBASEADAPTER_H
