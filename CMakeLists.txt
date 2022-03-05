cmake_minimum_required(VERSION 3.7)
project(JS_HelloWorld VERSION 0.0.1)

include(CTest)
enable_testing()

add_executable(JS_HelloWorld helloWorldJulia/src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPACK)