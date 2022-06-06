cmake_minimum_required(VERSION 3.14)
project(poker)
set(CMAKE_CXX_STANDARD 14)

add_library(poker_lib poker.cpp poker.h)

add_executable(poker main.cpp poker.h)
target_link_libraries(poker poker_lib)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_executable(testpoker poker_test.cpp poker.h)
target_link_libraries(testpoker gtest_main)
target_link_libraries(testpoker poker_lib)
