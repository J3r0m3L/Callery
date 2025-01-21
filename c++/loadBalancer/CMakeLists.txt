cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(LoadBalancer)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_library(sasProtolib "${CMAKE_CURRENT_SOURCE_DIR}/proto/StockAggregatesStoreService.proto")
target_link_libraries(sasProtolib gRPC::grpc++)
target_include_directories(sasProtolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate(TARGET sasProtolib LANGUAGE cpp)

protobuf_generate(TARGET sasProtolib LANGUAGE grpc 
GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
PLUGIN "protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("usr/local/include")
include_directories("/usr/include")

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(loadBalancer ${SOURCES})

target_link_libraries(loadBalancer sasProtolib)