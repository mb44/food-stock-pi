#ifndef _DATABASE_H
#define _DATABASE_H

#include <iostream>
#include <string>
#include "cjson.h"

class IDatabase {
  public:
    virtual ~IDatabase() {};
    virtual cJSON * getContainerItem(int) = 0;
    virtual int createContainerItem() = 0;
    virtual cJSON * deleteContainerItem(int) = 0;
    virtual cJSON * setMeasurement(int, float) = 0;
    virtual cJSON * setEmptyContainerWeight(int, float) = 0;
    virtual cJSON * setMaximumCapacity(int, float) = 0;
    virtual cJSON * getContainerState(int) = 0;
    virtual cJSON * setContainerState(int, const char*) = 0;
    virtual cJSON * getUpdateFrequency(int) = 0;
};

#endif
