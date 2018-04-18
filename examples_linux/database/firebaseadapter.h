#ifndef DATABASE_H
#define DATABASE_H

#include "idatabase.h"
#include <string>
#include <iostream>

class FirebaseAdapter : public IDatabase {
  public:
    virtual std::string getContainerItem(int containerId) override;
    virtual std::string createContainerItem(std::string containerItem) override;
    virtual std::string deleteContainerItem(int containerId) override;
    virtual std::string setMeasurement(int containerId, double measurement) override;
    virtual std::string setEmptyContainerWeight(int containerId, double measurement) override;
    virtual std::string setMaximumCapacity(int containerId, double maxCapacity) override;
    virtual std::string getContainerState(int containerId) override;
    virtual std::string setContainerState(int containerId, std::string state) override;
    virtual std::string getUpdateFrequency(int containerId) override;
};

#endif // FIREBASEADAPTER_H
