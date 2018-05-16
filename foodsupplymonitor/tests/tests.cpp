// tests.cpp
#include <gtest/gtest.h>
#include <stdint.h>
#include "stubs/radiostub.h"
#include "../radio/packer.h"
#include "mytest.cpp"
#include <cstring>

/******************************
* Test radio Pack/Unpack      *
******************************/ 

TEST(PackTestUpdateFrequency, UpdateFrequencyNegative) {
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
  // Expect pack() to return 1 (error)
  uint8_t expectedOutcome = 1;
  EXPECT_EQ(expectedOutcome, success);
}

TEST(PackTestUpdateFrequency, UpdateFrequencyScaleIdTooSmall) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};
  uint8_t messageType = 2;
  int updateFrequency = 30;
  int scaleId = -1;
  uint8_t success = packer->pack(payload, scaleId, messageType, updateFrequency);

  uint8_t expectedOutcome = 1;
  // Expect pack() to return 1 (error)
  EXPECT_EQ(expectedOutcome, success);
}

TEST(PackTestUpdateFrequency, ValidUpdateFrequency) {
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

TEST(PackTestPowerDown, PowerDownScaleIdTooSmall) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};
  int messageType = 2;
  int scaleId = -1;
  uint8_t success = packer->pack(payload, scaleId, messageType);

  uint8_t expectedOutcome = 1;
  // Expect pack() to return 1 (error)
  EXPECT_EQ(expectedOutcome, success);
}


TEST(PackTestPowerDown, PowerDownScaleIdTooLarge) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};
  int messageType = 2;
  int scaleId = 1050;
  uint8_t success = packer->pack(payload, scaleId, messageType);
  
  uint8_t expectedOutcome = 1;
  // Expect pack() to return 1 (error)
  EXPECT_EQ(expectedOutcome, success);
}

TEST(PackTestPowerDown, PowerDownValidData) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};
  int messageType = 2;
  int scaleId = 2;
  uint8_t success = packer->pack(payload, scaleId, messageType);
  char expected[payloadSize] =  { messageType, 0, 2, 0, 0, 0, 0 };
  // Expect comparison of arrays to yield true
  EXPECT_TRUE(0 == memcmp( expected, payload, payloadSize ));
}

TEST(UnPackTest, ValidUpdateFrequency) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0x02, 0, 0xD, 0, 0, 0x4, 0xB0};

  int scaleId = 0;
  uint8_t messageType = 0;
  int data = 0;
  int success = packer->unpack(payload, &scaleId, &messageType, &data);
  EXPECT_EQ(2, messageType);
  // Problem:
  EXPECT_EQ(13, scaleId);
  EXPECT_EQ(1200, data);
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
