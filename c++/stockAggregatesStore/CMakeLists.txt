cmake_minimum_required(VERSION 3.30.6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(StockAggregatesStore)

add_subdirectory(../sqlUtils ${CMAKE_BINARY_DIR}/sqlUtils)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("/usr/local/include")

find_package(SQLite3 REQUIRED)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(stockAggregatesStore ${SOURCES})

target_link_libraries(stockAggregatesStore sqlQueryBuilder SQLite3)
target_include_directories(stockAggregatesStore PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include SQLite::SQLite3)