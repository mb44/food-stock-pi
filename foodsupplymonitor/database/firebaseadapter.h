#ifndef FIREBASEADAPTER_H
#define FIREBASEADAPTER_H

#include "idatabase.h"
#include "auth.h"
#include <string>
#include <iostream>

class FirebaseAdapter : public IDatabase {
  private:
    FirebaseConfig cfg;
    IAuth *auth;
    // Authtoken = 945 characters + 1 for null-terminating null-character
    char authToken[AUTHTOKEN_LENGTH+1];
    cJSON *jsonReply;
    void authenticate();
    void parseConfig(char *firebaseConfig);
    void executeCURL(char *reply, const char *cmd);
  public:
    FirebaseAdapter(char *firebaseConfig);
    ~FirebaseAdapter();
    int containerItemExists(int containerId, int *exists) override;
    int createContainerItem(int containerId) override;
    int deleteContainerItem(int containerId) override;
    int setCurrentAmount(int containerId, float measurement) override;
    int setEmptyContainerWeight(int containerId, float measurement) override;
    int setMaximumCapacity(int containerId, float maxCapacity) override;
    int getContainerState(int containerId, char* state) override;
    int setContainerState(int containerId, const char *state) override;
    int getUpdateFrequency(int containerId, int *updateFrequency) override;
};

#endif // FIREBASEADAPTER_H
