cmake_minimum_required(VERSION 3.7)
project(DSA VERSION 0.0.1)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 11)

file(GLOB TEST_SOURCES "../app/test/*.cpp")
file(GLOB MAIN_SOURCES "../app/src/*.cpp")

add_executable(DSA.exe ../main/main.cpp ${MAIN_SOURCES})
add_executable(test.exe ../app/test/mainTests.cpp ${TEST_SOURCES} ${MAIN_SOURCES})

include_directories(${GTEST_INCLUDE_DIRS} ../app/include)
target_link_libraries(test.exe ${GTEST_LIBRARIES} pthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPACK)