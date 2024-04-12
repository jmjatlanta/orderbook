cmake_minimum_required(VERSION 3.0)

project(test_sd)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable( test_orderbook
    test.cpp
)

include(GoogleTest)

target_include_directories(test_orderbook PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(test_orderbook
    orderbook
    GTest::gtest_main
)
