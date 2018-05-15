// tests.cpp
#include <gtest/gtest.h>
#include <stdint.h>
#include "stubs/radiostub.h"
#include "../radio/packer.h"
#include "mytest.cpp"
#include <cstring>

/**************************
* Test radio Packing      *
**************************/ 
TEST(PackerTest, packUpdateFrequencyOK) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};
  uint8_t messageType = 1;
  // 425 = 1A9h
  int scaleId = 425;
  // 683 = 2ABh
  int updateFrequency = 683;
  int success = packer->pack(payload, scaleId, messageType, updateFrequency);
  char expected[payloadSize] =  { messageType, 0x1, 0xA9, 0, 0, 2, 0xAB };
  // Expect comparison of arrays to yield true
  EXPECT_TRUE(0 == memcmp( expected, payload, payloadSize ));
}

/*
TEST(PackerTest, packUpdateFrequencyNegativeBAD) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};
  uint8_t messageType = 1;
  // 425 = 1A9h
  int scaleId = 425;
  // 683 = 2ABh
  int updateFrequency = -25;
  uint8_t success = packer->pack(payload, scaleId, messageType, updateFrequency);

  char expected[payloadSize] =  { messageType, 0x1, 0xA9, 0, 0, 0x2, 0$
  // Expect comparison of arrays to yield true

  uint8_t expected = 1;
  EXPECT_EQ(expected, success);
}
*/
/*
TEST(PackerTest, packPowerDownOK) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};  
  int messageType = 2; 
  int scaleId = 2;
  packer->pack(payload, scaleId, messageType);

  char expected[payloadSize] =  { messageType, 0, 2, 0, 0, 0, 0 };
  // Expect comparison of arrays to yield true
  EXPECT_TRUE(0 == memcmp( expected, payload, payloadSize ));
}
*/ 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
