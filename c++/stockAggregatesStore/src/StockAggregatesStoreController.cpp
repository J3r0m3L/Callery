#include "StockAggregatesStoreImpl.hpp"

#include <grpcpp/grpcpp.h>
#include <memory>

using std::unique_ptr;

int main() {
    StockAggregatesStoreImpl service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:8080", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();
}