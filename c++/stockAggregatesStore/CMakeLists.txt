cmake_minimum_required(VERSION 3.10)

project(StockAggregatesStore)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(../sqlUtils ${CMAKE_BINARY_DIR}/build)

add_executable(StockAggregatesStore src/Main.cpp)

target_link_libraries(StockAggregatesStore SqlQueryBuilder)
target_include_directories(StockAggregatesStore
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../sqlUtils/include
)