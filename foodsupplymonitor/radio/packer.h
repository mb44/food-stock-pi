#ifndef PACKER_H
#define PACKER_H

#include "ipacker.h"

class Packer : public IPacker{
  public:
    ~Packer();
    void pack(char *payload, int scaleId, int messageType) override;
    void pack(char *payload, int scaleId, int messageType, int updateFrequency) override;
};

#endif // PACKER_H
