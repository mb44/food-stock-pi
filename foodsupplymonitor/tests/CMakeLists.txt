cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ../radio/packer.cpp stubs/rf24stub.cpp ../database/cjson.c ../database/auth.cpp ../database/firebaseadapter.cpp stubs/resthandlerupdatefrequencyfake1.cpp stubs/resthandlerupdatefrequencyfake2.cpp stubs/resthandlercontaineritemsfake.cpp tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
