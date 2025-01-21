#include "proto/StockAggregatesStoreService.grpc.pb.h"
#include "proto/StockAggregatesStoreService.pb.h"
#include "StockAggregatesTable.hpp"

#include <google/protobuf/empty.pb.h>
#include <grpcpp/grpcpp.h>

using grpc::Status;
using grpc::ServerContext;
using SasPkg::SasTableQuery;
using SasPkg::SasTableMsgs;
using SasPkg::SasTickers;


class StockAggregatesStoreImpl : public SasPkg::StockAggregatesStoreService::Service {

private: 
  StockAggregatesTable table = StockAggregatesTable("StockAggregates", "./service/StockData.db");

public: 
  Status queryStockAggregatesTable(ServerContext* context, const SasTableQuery* request, SasTableMsgs* response) override;
  Status getStockTickers(ServerContext* context, const google::protobuf::Empty* request, SasTickers* response) override;
};