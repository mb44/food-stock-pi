#ifndef _DATABASE_H
#define _DATABASE_H

#include <iostream>
#include <string>
#include "cjson.h"

class IDatabase {
  public:
    virtual ~IDatabase() { std::cout << "IDatabase destructed" << std::endl; };
    virtual cJSON * getContainerItem(int) = 0;
    virtual std::string createContainerItem(std::string) = 0;
    virtual std::string deleteContainerItem(int) = 0;
    virtual std::string setMeasurement(int, double) = 0;
    virtual std::string setEmptyContainerWeight(int, double) = 0;
    virtual std::string setMaximumCapacity(int, double) = 0;
    virtual std::string getContainerState(int) = 0;
    virtual std::string setContainerState(int, std::string) = 0;
    virtual std::string getUpdateFrequency(int) = 0;
};

#endif
