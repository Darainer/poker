cmake_minimum_required(VERSION 3.10)
project(poker)
set(CMAKE_CXX_STANDARD 14)

add_executable(poker main.cpp poker.h )

add_subdirectory(googletest)
add_executable(testpoker poker_test.cpp poker.h)
target_link_libraries(testpoker gtest_main)
