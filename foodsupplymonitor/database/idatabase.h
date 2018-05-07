#ifndef _DATABASE_H
#define _DATABASE_H

#include "dbdefines.h"
#include <iostream>
#include <string>
#include "cjson.h"

class IDatabase {
  public:
    virtual ~IDatabase() {};
    //virtual cJSON * getContainerItem(int) = 0;
    virtual int createContainerItem(int) = 0;
    virtual int deleteContainerItem(int) = 0;
    virtual int setMeasurement(int, float) = 0;
    virtual int setEmptyContainerWeight(int, float) = 0;
    virtual int setMaximumCapacity(int, float) = 0;
    virtual int getContainerState(int, char*) = 0;
    virtual int setContainerState(int, const char*) = 0;
    virtual int getUpdateFrequency(int, int*) = 0;
};

#endif
