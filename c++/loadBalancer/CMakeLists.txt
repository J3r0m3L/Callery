cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(LoadBalancer)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("usr/local/include")

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(loadBalancer ${SOURCES})

target_include_directories(loadBalancer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)