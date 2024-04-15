cmake_minimum_required(VERSION 3.2)

project(bench_orderbook)

find_package(benchmark REQUIRED)

add_executable(bench_orderbook
    bench.cpp
)

target_include_directories( bench_orderbook PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(bench_orderbook
    orderbook
    benchmark::benchmark
)

