cmake_minimum_required(VERSION 3.7)
project(DC_test VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(DC_test main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
