cmake_minimum_required(VERSION 3.14)
project(selection_sort_tests)

# Require C++20 for GoogleTest and modern C++ features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download and make GoogleTest available
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add your test executable (add source files as needed)
add_executable(selection_sort_test selection_sort_test.cpp selection_sort.hpp)

# Link the test executable with GoogleTest
target_link_libraries(selection_sort_test GTest::gtest_main)

# Enable test discovery for CTest
include(GoogleTest)
gtest_discover_tests(selection_sort_test)