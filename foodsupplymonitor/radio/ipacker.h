#ifndef IPACKER_H
#define IPACKER_H

class IPacker {
  public:
    virtual ~IPacker() {}
    virtual void pack(char *payload, int scaleId, int messageType) = 0;
    virtual void pack(char *payload, int scaleId, int messageType, int updateFrequency) = 0;
};

#endif // IPACKER_H
