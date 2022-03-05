cmake_minimum_required(VERSION 3.7)
project(DC_test)
set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(sdl2_image REQUIRED  SDL2_image)
pkg_check_modules(sdl2_ttf REQUIRED SDL2_ttf)

add_executable(main ../src/main.cpp)

target_include_directories(main PRIVATE ${sdl2_image_INCLUDE_DIRS})
target_link_libraries(main PRIVATE ${sdl2_image_LINK_LIBRARIES})
target_include_directories(main PRIVATE ${sdl2_ttf_INCLUDE_DIRS})
target_link_libraries(main PRIVATE ${sdl2_ttf_LINK_LIBRARIES})