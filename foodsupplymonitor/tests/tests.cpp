// tests.cpp
#include <gtest/gtest.h>
#include "mytest.cpp"
#include "radiostub.h"
 
TEST(PackTest, packPowerDown) {
  const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
  RadioStub radio(pipes);
  int messageType = 2; 
  int scaleId = 2;
  radio.pack(scaleId, messageType);

  ASSERT_EQ(messageType, radio.sendPayload[0]);
  ASSERT_EQ(0, radio.sendPayload[1]);
  ASSERT_EQ(2, radio.sendPayload[2]);
}


TEST(PackTest, packUpdateFrequency) {
  const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
  RadioStub radio(pipes);
  int messageType = 2;
  // 230 = 139h
  int scaleId = 313;
  // 3600 = E10h
  int updateFrequency = 3600;
  radio.pack(scaleId, messageType, updateFrequency);

  ASSERT_EQ(messageType, radio.sendPayload[0]);
  ASSERT_EQ(0x1, radio.sendPayload[1]);
  ASSERT_EQ(0x39, radio.sendPayload[2]);
  ASSERT_EQ(0, radio.sendPayload[3]);
  ASSERT_EQ(0, radio.sendPayload[4]);
  ASSERT_EQ(0xE, radio.sendPayload[5]);
  ASSERT_EQ(0x10, radio.sendPayload[6]);
}

TEST(SquareRootTest, PositiveNos) { 
    ASSERT_EQ(6, squareRoot(36.0));
    ASSERT_EQ(18.0, squareRoot(324.0));
    ASSERT_EQ(25.4, squareRoot(645.16));
    ASSERT_EQ(0, squareRoot(0.0));
}
 
TEST(SquareRootTest, NegativeNos) {
    ASSERT_EQ(-1.0, squareRoot(-15.0));
    ASSERT_EQ(-1.0, squareRoot(-0.2));
}


 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
