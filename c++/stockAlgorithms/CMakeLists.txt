cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(StockAlgorithms)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_library(protolib "${CMAKE_CURRENT_SOURCE_DIR}/proto/StockAlgorithmsService.proto")
target_link_libraries(protolib gRPC::grpc++)
target_include_directories(protolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate(TARGET protolib LANGUAGE cpp)

protobuf_generate(TARGET protolib LANGUAGE grpc 
GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
PLUGIN "protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("usr/local/include")

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(stockAlgorithms ${SOURCES})

file(GLOB TEST "${CMAKE_CURRENT_SOURCE_DIR}/test/src/Test.cpp")
file(GLOB DICKY_FULLER "${CMAKE_CURRENT_SOURCE_DIR}/src/DickyFuller.cpp")
add_executable(stockAlgorithmsTest ${TEST} ${DICKY_FULLER})

target_link_libraries(stockAlgorithms protolib)