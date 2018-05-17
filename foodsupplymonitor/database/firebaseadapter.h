#ifndef FIREBASEADAPTER_H
#define FIREBASEADAPTER_H

#include "idatabase.h"
#include "iauth.h"
#include <string>
#include <iostream>
#include "iresthandler.h"

class FirebaseAdapter : public IDatabase {
  private:
    FirebaseConfig cfg;
    const char *configPath;
    IAuth *auth;
    IRESTHandler *rest;
    // Authtoken = 945 characters + 1 for null-terminating null-character
    char authToken[AUTHTOKEN_LENGTH+1];
    cJSON *jsonReply;
    void parseConfig();
  public:
    FirebaseAdapter(IAuth *auth, IRESTHandler *rest, const char *configPath);
    ~FirebaseAdapter();

    uint8_t authenticate();

    uint8_t containerItemExists(int containerId, uint8_t *exists) override;
    uint8_t createContainerItem(int containerId) override;
    uint8_t setCurrentAmount(int containerId, float currentAmount) override;
    uint8_t setEmptyContainerWeight(int containerId, float emptyContainerWeight) override;
    uint8_t setMaximumCapacity(int containerId, float maximumCapacity) override;
    uint8_t getContainerState(int containerId, char* state) override;
    uint8_t setContainerState(int containerId, const char *state) override;
    uint8_t getUpdateFrequency(int containerId, int *updateFrequency) override;
};

#endif // FIREBASEADAPTER_H
