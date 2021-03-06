// tests.cpp
#include <gtest/gtest.h>
#include <stdint.h>
#include "stubs/rf24stub.h"
#include "../database/firebaseadapter.h"
#include "stubs/resthandlerupdatefrequencyfake1.h"
#include "stubs/resthandlerupdatefrequencyfake2.h"
#include "stubs/resthandlercontaineritemsfake.h"
#include "../radio/packer.h"
#include "../database/resthandler.h"
#include "../database/auth.h"
#include "mytest.cpp"
#include <cstring>

/******************************
* Test Pack RF24Packer        *
******************************/ 

TEST(Packer_Pack, UpdateFrequencyNegative) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};
  uint8_t messageType = 1;
  // 425 = 1A9h
  int scaleId = 425;
  // 683 = 2ABh
  int updateFrequency = -25;
  uint8_t result = packer->pack(payload, scaleId, messageType, updateFrequency);
  // Expect pack() to return 1 (error)
  uint8_t expectedOutcome = 1;
  EXPECT_EQ(expectedOutcome, result);
}

TEST(Packer_Pack, UpdateFrequencyScaleIdTooSmall) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};
  uint8_t messageType = 2;
  int updateFrequency = 30;
  int scaleId = -1;
  uint8_t result = packer->pack(payload, scaleId, messageType, updateFrequency);

  uint8_t expectedOutcome = 1;
  // Expect pack() to return 1 (error)
  EXPECT_EQ(expectedOutcome, result);
}

TEST(Packer_Pack, ValidUpdateFrequency) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};
  uint8_t messageType = 1;
  // 425 = 1A9h
  int scaleId = 425;
  // 683 = 2ABh
  int updateFrequency = 683;
  int result = packer->pack(payload, scaleId, messageType, updateFrequency);
  char expected[payloadSize] =  { messageType, 0x1, 0xA9, 0, 0, 2, 0xAB };
  // Expect comparison of arrays to yield true
  EXPECT_TRUE(0 == memcmp( expected, payload, payloadSize ));
}

TEST(Packer_Pack, PowerDownScaleIdTooSmall) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};
  uint8_t messageType = 2;
  int scaleId = -1;
  uint8_t result = packer->pack(payload, scaleId, messageType);

  uint8_t expectedOutcome = 1;
  // Expect pack() to return 1 (error)
  EXPECT_EQ(expectedOutcome, result);
}

TEST(Packer_Pack, PowerDownScaleIdTooLarge) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};
  uint8_t messageType = 2;
  int scaleId = 1050;
  uint8_t result = packer->pack(payload, scaleId, messageType);
  
  uint8_t expectedOutcome = 1;
  // Expect pack() to return 1 (error)
  EXPECT_EQ(expectedOutcome, result);
}

TEST(Packer_Pack, PowerDownValidData) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0, 0, 0, 0, 0, 0, 0};
  uint8_t messageType = 2;
  int scaleId = 2;
  uint8_t result = packer->pack(payload, scaleId, messageType);
  char expected[payloadSize] =  { messageType, 0, 2, 0, 0, 0, 0 };
  // Expect comparison of arrays to yield true
  EXPECT_TRUE(0 == memcmp( expected, payload, payloadSize ));
}

TEST(Packer_Unpack, ScaleIdToLarge) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0x2, 0x3, 0xFC, 0, 0, 30 };
  // Integer size on Raspberry Pi: 4bytes. Most significant bit set: number is negative
  int scaleId = 0x0;
  uint8_t messageType = 0;
  int data = 0;

  int result = packer->unpack(payload, &scaleId, &messageType, &data);
  uint8_t expectedSuccess = 1;
  EXPECT_EQ(expectedSuccess, result);
}

TEST(Packer_Unpack, ValidUpdateFrequency) {
  Packer p;
  IPacker *packer = &p;
  int payloadSize = 7;
  char payload[payloadSize] = { 0x2, 0, 0xD, 0, 0, 0x4, 0xB0 };

  int scaleId = 0;
  uint8_t messageType = 0;
  int data = 0;
  uint8_t result = packer->unpack(payload, &scaleId, &messageType, &data);

  EXPECT_EQ(2, messageType);
  EXPECT_EQ(13, scaleId);
  EXPECT_EQ(1200, data);
}

/******************************
* Test RF24Adapter (dummy)    *
******************************/
TEST(RF24Adapter_SetUpdateFrequency, UpdateFrequencyNegative) {
  Packer p;
  IPacker *packer = &p;

  uint64_t dummyPipes[2] = {0, 0};
  RF24Stub radio(dummyPipes, packer);
  int scaleId = 14;
  int updateFrequency = -25;
  uint8_t result = radio.setUpdateFrequency(scaleId, updateFrequency);
  // Expect setUpdateFrequency() to return 1 (error)
  uint8_t expectedOutcome = 1;
  EXPECT_EQ(expectedOutcome, result);
}

TEST(RF24Adapter_SetUpdateFrequency, ScaleIdNegative) {
  Packer p;
  IPacker *packer = &p;

  uint64_t dummyPipes[2] = {0, 0};
  RF24Stub radio(dummyPipes, packer);
  int scaleId = -7;
  int updateFrequency = 30;
  uint8_t result = radio.setUpdateFrequency(scaleId, updateFrequency);
  // Expect setUpdateFrequency() to return 1 (error)
  uint8_t expectedOutcome = 1;
  EXPECT_EQ(expectedOutcome, result);
}

TEST(RF24Adapter_SetUpdateFrequency, ScaleIdTooLarge) {
  Packer p;
  IPacker *packer = &p;

  uint64_t dummyPipes[2] = {0, 0};
  RF24Stub radio(dummyPipes, packer);
  int scaleId = 1050;
  int updateFrequency = 30;
  uint8_t result = radio.setUpdateFrequency(scaleId, updateFrequency);
  // Expect setUpdateFrequency() to return 1 (error)
  uint8_t expectedOutcome = 1;
  EXPECT_EQ(expectedOutcome, result);
}

TEST(RF24AdapterSetUpdateFrequency, ValidData) {
  Packer p;
  IPacker *packer = &p;

  uint64_t dummyPipes[2] = {0, 0};
  RF24Stub radio(dummyPipes, packer);
  int scaleId = 13;
  int updateFrequency = 30;
  uint8_t result = radio.setUpdateFrequency(scaleId, updateFrequency);
  // Expect setUpdateFrequency() to return 1 (error)
  uint8_t expectedOutcome = 0;
  EXPECT_EQ(expectedOutcome, result);
}

TEST(RF24Adapter_PowerDown, ScaleIdNegative) {
  Packer p;
  IPacker *packer = &p;

  uint64_t dummyPipes[2] = {0, 0};
  RF24Stub radio(dummyPipes, packer);
  int scaleId = -30;
  uint8_t result = radio.powerDown(scaleId);
  // Expect setUpdateFrequency() to return 1 (error)
  uint8_t expectedOutcome = 1;
  EXPECT_EQ(expectedOutcome, result);
}

TEST(RF24Adapter_PowerDown, ScaleIdTooLarge) {
  Packer p;
  IPacker *packer = &p;

  uint64_t dummyPipes[2] = {0, 0};
  RF24Stub radio(dummyPipes, packer);
  int scaleId = 1050;
  uint8_t result = radio.powerDown(scaleId);
  // Expect setUpdateFrequency() to return 1 (error)
  uint8_t expectedOutcome = 1;

  EXPECT_EQ(expectedOutcome, result);
}

/******************************
* Test FirebaseAdapter        *
******************************/
TEST(FirebaseAdapter_GetUpdateFrequency, NegativeUpdateFrequency) {
  RESTHandlerUpdateFrequencyFake1 r;
  IRESTHandler *rest = &r;
  
  Auth a(rest);
  IAuth *auth = &a;

  FirebaseAdapter d(auth, rest, "../firebaseConfig.txt");
  IDatabase *db = &d;

  int scaleId = 13;
  int updateFrequency = 0;
  uint8_t result = db->getUpdateFrequency(scaleId, &updateFrequency);
  uint8_t expected = 1;
  EXPECT_EQ(expected, result);
}

TEST(FirebaseAdapter_GetUpdateFrequency, UpdateFrequencyValid) {
  RESTHandlerUpdateFrequencyFake2 r;
  IRESTHandler *rest = &r;

  Auth a(rest);
  IAuth *auth = &a;

  FirebaseAdapter d(auth, rest, "../firebaseConfig.txt");
  IDatabase *db = &d;

  int scaleId = 13;
  int updateFrequency = 0;
  uint8_t result = db->getUpdateFrequency(scaleId, &updateFrequency);

  uint8_t expectedResult = 0;
  int expectedUpdateFrequency = 45;

  EXPECT_EQ(expectedResult, result);
  EXPECT_EQ(expectedUpdateFrequency, updateFrequency);
}


// -----
TEST(FirebaseAdapter_ContainerItemExists, ScaleIdNegative) {
  RESTHandlerContainerItemsFake r;
  IRESTHandler *rest = &r;

  Auth a(rest);
  IAuth *auth = &a;

  FirebaseAdapter d(auth, rest, "../firebaseConfig.txt");
  IDatabase *db = &d;

  int scaleId = -1;
  uint8_t exists = 0;
  uint8_t result = db->containerItemExists(scaleId, &exists);

  uint8_t expectedResult = 1;

  EXPECT_EQ(expectedResult, result);
}

TEST(FirebaseAdapter_ContainerItemExists, ScaleIdEQ0) {
  RESTHandlerContainerItemsFake r;
  IRESTHandler *rest = &r;

  Auth a(rest);
  IAuth *auth = &a;

  FirebaseAdapter d(auth, rest, "../firebaseConfig.txt");
  IDatabase *db = &d;

  int scaleId = 0;
  uint8_t exists = 1;
  uint8_t result = db->containerItemExists(scaleId, &exists);

  uint8_t expectedResult = 0;
  uint8_t expectedExists = 0;
  EXPECT_EQ(expectedExists, exists);
  EXPECT_EQ(expectedResult, result);
}

TEST(FirebaseAdapter_ContainerItemExists, ScaleIdEQ1) {
  RESTHandlerContainerItemsFake r;
  IRESTHandler *rest = &r;

  Auth a(rest);
  IAuth *auth = &a;

  FirebaseAdapter d(auth, rest, "../firebaseConfig.txt");
  IDatabase *db = &d;

  int scaleId = 1;
  uint8_t exists = 0;
  uint8_t result = db->containerItemExists(scaleId, &exists);

  uint8_t expectedResult = 0;
  uint8_t expectedExists = 0;
  EXPECT_EQ(expectedResult, result);
  EXPECT_EQ(expectedExists, exists);
}

TEST(FirebaseAdapter_ContainerItemExists, ScaleIdEQ3) {
  RESTHandlerContainerItemsFake r;
  IRESTHandler *rest = &r;

  Auth a(rest);
  IAuth *auth = &a;

  FirebaseAdapter d(auth, rest, "../firebaseConfig.txt");
  IDatabase *db = &d;

  int scaleId = 3;
  uint8_t exists = 1;
  uint8_t result = db->containerItemExists(scaleId, &exists);

  uint8_t expectedResult = 0;
  uint8_t expectedExists = 0;
  EXPECT_EQ(expectedExists, exists);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
