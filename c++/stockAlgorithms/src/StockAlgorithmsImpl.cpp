#include "DickyFuller.hpp"
#include "proto/StockAlgorithmsService.grpc.pb.h"
#include "proto/StockAlgorithmsService.pb.h"
#include "StockAlgorithmsImpl.hpp"

#include <grpcpp/grpcpp.h>
#include <vector>

using grpc::Status;
using grpc::ServerContext;
using SaPkg::SaDickyFullerRequest;
using SaPkg::SaDickyFullerResponse;
using std::vector;

Status StockAlgorithmsImpl::dickyFullerTest(ServerContext* context, const SaDickyFullerRequest* request, SaDickyFullerResponse* response) {

  vector<float> stockPrices; 
  for (auto& price : request->stockprices()) {
    stockPrices.emplace_back(price);
  }

  float tStat = DickyFuller::testWithTrendAndConstant(stockPrices, 1);
  response->set_tstat(tStat);

  return Status::OK;

}
