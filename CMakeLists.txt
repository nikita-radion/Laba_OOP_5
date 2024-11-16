cmake_minimum_required(VERSION 3.10)
project(forward_list)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(forward_list_lib
    src/dynamic_memory_resource.cpp
)

enable_testing()
add_executable(tests tests/tests.cpp)
target_link_libraries(tests 
    GTest::gtest_main
    forward_list_lib
)

add_executable(forward_list_app src/main.cpp)
target_link_libraries(forward_list_app forward_list_lib)

include(GoogleTest)
gtest_discover_tests(tests)