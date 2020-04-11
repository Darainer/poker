cmake_minimum_required(VERSION 3.10)
project(poker)
set(CMAKE_CXX_STANDARD 14)

add_library(poker_lib poker.cpp poker.h)

add_executable(poker main.cpp poker.h)
target_link_libraries(poker poker_lib)

add_subdirectory(googletest)
add_executable(testpoker poker_test.cpp poker.h)
target_link_libraries(testpoker gtest_main)
target_link_libraries(testpoker poker_lib)
