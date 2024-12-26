cmake_minimum_required(VERSION 3.30.6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SqlQueryBuilder)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("/usr/local/include")

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(sqlQueryBuilder STATIC ${SOURCES})

target_include_directories(sqlQueryBuilder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)