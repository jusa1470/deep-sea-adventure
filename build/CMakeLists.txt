cmake_minimum_required(VERSION 3.7)
project(DSA VERSION 0.0.1)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 11)
find_package(PkgConfig REQUIRED)
pkg_check_modules(sdl2_image REQUIRED  SDL2_image)
pkg_check_modules(sdl2_ttf REQUIRED SDL2_ttf)

file(GLOB TEST_SOURCES "../app/test/*.cpp")
file(GLOB MAIN_SOURCES "../app/src/*.cpp")

add_executable(DSA.exe ../main/main.cpp ${MAIN_SOURCES})
add_executable(test.exe ../app/test/mainTests.cpp ${TEST_SOURCES} ${MAIN_SOURCES})

target_include_directories(test.exe PRIVATE ${GTEST_INCLUDE_DIRS} ../app/include ${sdl2_image_INCLUDE_DIRS})
target_link_libraries(test.exe PRIVATE ${GTEST_LIBRARIES} pthread ${sdl2_image_LINK_LIBRARIES})
target_include_directories(DSA.exe PRIVATE ../app/include ${sdl2_image_INCLUDE_DIRS})
target_link_libraries(DSA.exe PRIVATE ${sdl2_image_LINK_LIBRARIES})



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPACK)