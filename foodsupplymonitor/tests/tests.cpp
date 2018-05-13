// tests.cpp
#include <gtest/gtest.h>
#include "stubs/radiostub.h"
#include "../radio/packer.h"
#include "mytest.cpp"
#include <cstring>

/**************************
* Test radio Packing      *
**************************/
 
TEST(PackTest, packUpdateFrequency) {
  Packer p;
  IPacker *packer = &p;
  char payload[7] = { 0, 0, 0, 0, 0, 0, 0};
  int messageType = 1;
  // 425 = 1A9h
  int scaleId = 425;
  // 683 = 2ABh
  int updateFrequency = 683;
  packer->pack(payload, scaleId, messageType, updateFrequency);

  char expected[7] =  { messageType, 0x1, 0xA9, 0, 0, 0x2, 0xAB };
  // Expect comparison of arrays to yield true
  EXPECT_TRUE(0 == memcmp( expected, payload, 7 ));
}

TEST(PackTest, packPowerDown) {
  Packer p;
  IPacker *packer = &p;
  char payload[7] = { 0, 0, 0, 0, 0, 0, 0};  
  int messageType = 2; 
  int scaleId = 2;
  packer->pack(payload, scaleId, messageType);

  char expected[7] =  { messageType, 0, 2, 0, 0, 0, 0 };
  // Expect comparison of arrays to yield true
  EXPECT_TRUE(0 == memcmp( expected, payload, 7 ));
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
