#ifndef IDATABASE_H
#define IDATABASE_H

#include "../defines.h"
#include "dbdefines.h"
#include <iostream>
#include <string>
#include "cjson.h"

/*! \file idatabase.h
    \brief Interface for database operations
*/
class IDatabase {
  public:
    virtual ~IDatabase() {}
    virtual uint8_t containerItemExists(int, uint8_t*) = 0;
    virtual uint8_t createContainerItem(int) = 0;
    virtual uint8_t setCurrentAmount(int, float) = 0;
    virtual uint8_t setEmptyContainerWeight(int, float) = 0;
    virtual uint8_t setMaximumCapacity(int, float) = 0;
    virtual uint8_t getContainerState(int, char*) = 0;
    virtual uint8_t setContainerState(int, const char*) = 0;
    virtual uint8_t getUpdateFrequency(int, int*) = 0;
};

#endif
