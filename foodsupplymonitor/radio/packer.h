#ifndef PACKER_H
#define PACKER_H

#include "ipacker.h"

/*! \file packer.h
    \brief Implementation of pack and unpack functionality.
*/

class Packer : public IPacker {
  public:
    ~Packer();
    uint8_t pack(char *payload, const int scaleId, const uint8_t messageType) override;
    uint8_t pack(char *payload, int scaleId, uint8_t messageType, int updateFrequency) override;
    uint8_t unpack(const char *payload, int *scaleId, uint8_t *messageType, int *data) override;
};

#endif // PACKER_H
