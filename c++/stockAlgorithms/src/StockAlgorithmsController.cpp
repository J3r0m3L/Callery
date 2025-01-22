#include "StockAlgorithmsImpl.hpp"

#include <grpcpp/grpcpp.h>
#include <memory>

using std::unique_ptr;

int main() {
    StockAlgorithmsImpl service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:8082", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();
}