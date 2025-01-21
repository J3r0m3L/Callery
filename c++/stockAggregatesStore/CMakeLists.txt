cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(StockAggregatesStore)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_library(protolib "${CMAKE_CURRENT_SOURCE_DIR}/proto/StockAggregatesStoreService.proto")
target_link_libraries(protolib gRPC::grpc++)
target_include_directories(protolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate(TARGET protolib LANGUAGE cpp)

protobuf_generate(TARGET protolib LANGUAGE grpc 
GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
PLUGIN "protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin")

find_package(SQLite3 REQUIRED)
add_subdirectory(../sqlUtils ${CMAKE_BINARY_DIR}/sqlUtils)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("/usr/local/include")
include_directories("/usr/include")

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(stockAggregatesStore ${SOURCES})

target_link_libraries(stockAggregatesStore sqlQueryBuilder SQLite::SQLite3 protolib)