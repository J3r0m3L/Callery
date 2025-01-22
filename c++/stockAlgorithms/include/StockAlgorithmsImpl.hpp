#pragma once 

#include "proto/StockAlgorithmsService.grpc.pb.h"
#include "proto/StockAlgorithmsService.pb.h"

#include <grpcpp/grpcpp.h>

using grpc::Status;
using grpc::ServerContext;
using SaPkg::SaDickyFullerRequest;
using SaPkg::SaDickyFullerResponse;

class StockAlgorithmsImpl : public SaPkg::StockAlgorithmsService::Service {

public:
  Status dickyFullerTest(ServerContext* context, const SaDickyFullerRequest* request, SaDickyFullerResponse* response) override;

};