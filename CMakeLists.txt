cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(orderbook VERSION 1.0.0 LANGUAGES CXX)

find_package(Boost REQUIRED)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(test)
set(BENCHMARK_ENABLE_GTEST_TESTS NO)
add_subdirectory(benchmark)
add_subdirectory(bench)

add_library(orderbook
    orderbook.cpp
)

target_include_directories(orderbook PRIVATE
    ${Boost_INCLUDE_DIR}
)

