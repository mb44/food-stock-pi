#ifndef _DATABASE_H
#define _DATABASE_H

#include <iostream>
#include <string>

class IDatabase {
  public:
    virtual std::string getContainerItem(int) = 0;
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
