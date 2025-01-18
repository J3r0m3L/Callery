cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(StockAlgorithms)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("usr/local/include")

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(stockAlgorithms ${SOURCES})

file(GLOB TEST "${CMAKE_CURRENT_SOURCE_DIR}/test/src/Test.cpp")
file(GLOB DICKY_FULLER "${CMAKE_CURRENT_SOURCE_DIR}/src/DickyFuller.cpp")
add_executable(stockAlgorithmsTest ${TEST} ${DICKY_FULLER})

target_include_directories(stockAlgorithms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)