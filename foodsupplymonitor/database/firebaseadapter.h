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
    // Authtoken = 945 characters + 1 for null-terminating null-character
    char authToken[AUTHTOKEN_LENGTH+1];
    cJSON *jsonReply;
    void parseConfig(char *firebaseConfig);
    void executeCURL(char *reply, const char *cmd);
  public:
    FirebaseAdapter(char *firebaseConfig);
    virtual ~FirebaseAdapter();
    void authenticate();
    //cJSON * getContainerItem(int containerId) override;
    int createContainerItem(int containerId) override;
    int deleteContainerItem(int containerId) override;
    int setMeasurement(int containerId, float measurement) override;
    int setEmptyContainerWeight(int containerId, float measurement) override;
    int setMaximumCapacity(int containerId, float maxCapacity) override;
    int getContainerState(int containerId, char* state) override;
    int setContainerState(int containerId, const char *state) override;
    int getUpdateFrequency(int containerId, int *updateFrequency) override;
};

#endif // FIREBASEADAPTER_H
