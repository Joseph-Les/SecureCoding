cmake_minimum_required(VERSION 3.10)
project(Module4)

# Add Google Test
add_subdirectory(googletest)

# Include directories
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add your test files
add_executable(runTests test.cpp)

# Link Google Test
target_link_libraries(runTests gtest gtest_main)
