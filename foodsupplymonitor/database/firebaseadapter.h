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
    IAuth *auth;
    IRESTHandler *rest;
    // Authtoken = 945 characters + 1 for null-terminating null-character
    char authToken[AUTHTOKEN_LENGTH+1];
    cJSON *jsonReply;
    void authenticate();
    void parseConfig(const char *firebaseConfig);
    // void executeCURL(char *reply, const char *cmd);
  public:
    FirebaseAdapter(IAuth *auth, IRESTHandler *rest, const char *firebaseConfig);
    ~FirebaseAdapter();
    uint8_t containerItemExists(int containerId, int *exists) override;
    uint8_t createContainerItem(int containerId) override;
    uint8_t setCurrentAmount(int containerId, float currentAmount) override;
    uint8_t setEmptyContainerWeight(int containerId, float emptyContainerWeight) override;
    uint8_t setMaximumCapacity(int containerId, float maximumCapacity) override;
    uint8_t getContainerState(int containerId, char* state) override;
    uint8_t setContainerState(int containerId, const char *state) override;
    uint8_t getUpdateFrequency(int containerId, int *updateFrequency) override;
};

#endif // FIREBASEADAPTER_H
