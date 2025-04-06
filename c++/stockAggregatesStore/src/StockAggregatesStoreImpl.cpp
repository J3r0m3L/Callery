#include "proto/StockAggregatesStoreService.grpc.pb.h"
#include "proto/StockAggregatesStoreService.pb.h"
#include "StockAggregatesStoreImpl.hpp"
#include "StockAggregatesTable.hpp"
#include "StockAggregatesTableMessage.hpp"

#include <grpcpp/grpcpp.h>
#include <optional>
#include <string>
#include <utility>
#include <vector>

using grpc::ServerContext;
using grpc::Status;
using SasPkg::SasTableQuery;
using SasPkg::SasTableMsgs;
using std::make_pair;
using std::optional;
using std::pair;
using std::string;
using std::vector;

Status StockAggregatesStoreImpl::queryStockAggregatesTable(ServerContext* context, const SasTableQuery* request, SasTableMsgs* response) {
  optional<string> ticker;
  optional<pair<long long, long long>> timestampRange;
  optional<pair<float, float>> closeRange;
  optional<pair<float, float>> highRange;
  optional<pair<float, float>> lowRange;
  optional<pair<float, float>> transactionsRange;
  optional<pair<float, float>> openRange;
  optional<pair<float, float>> volumeRange;
  optional<pair<float, float>> vwapRange;

  if (request->has_ticker()) {
    ticker = request->ticker();
  }
  if (request->timestamprange().size() == 2) {
    timestampRange = make_pair(request->timestamprange().at(0), request->timestamprange().at(1));
  }
  if (request->closerange().size() == 2) {
    closeRange = make_pair(request->closerange().at(0), request->closerange().at(1));
  }
  if (request->highrange().size() == 2) {
    highRange = make_pair(request->highrange().at(0), request->highrange().at(1));
  }
  if (request->lowrange().size() == 2) {
    lowRange = make_pair(request->lowrange().at(0), request->lowrange().at(1));
  }
  if (request->transactionsrange().size() == 2) {
    transactionsRange = make_pair(request->transactionsrange().at(0), request->transactionsrange().at(1));
  }
  if (request->openrange().size() == 2) {
    openRange = make_pair(request->openrange().at(0), request->openrange().at(1));
  }
  if (request->volumerange().size() == 2) {
    volumeRange = make_pair(request->volumerange().at(0), request->volumerange().at(1));
  }
  if (request->vwaprange().size() == 2) {
    vwapRange = make_pair(request->vwaprange().at(0), request->vwaprange().at(1));
  }

  vector<StockAggregatesTableMessage> msgs = table.queryStockAggregatesTable(StockAggregatesTableQuery(
    ticker,
    timestampRange,
    closeRange,
    highRange,
    lowRange,
    transactionsRange,
    openRange,
    volumeRange,
    vwapRange 
  ));

  // transfering too much data (stock prices every minute) for default protobuf size so sampling every 60th
  for (int i = 0; i < msgs.size(); i+=60) {
    auto& msg = msgs.at(i);
    auto* data = response->mutable_msgs()->Add();
    data->set_ticker(msg.getTicker());
    data->set_timestamp(msg.getTimestamp());
    data->set_close(msg.getClose());
    data->set_high(msg.getHigh());
    data->set_low(msg.getLow());
    data->set_transactions(msg.getTransactions());
    data->set_open(msg.getOpen());
    data->set_volume(msg.getVolume());
    data->set_vwap(msg.getVwap()); 
  }
  
  return Status::OK;
}


Status StockAggregatesStoreImpl::getStockTickers(ServerContext* context, const google::protobuf::Empty* request, SasTickers* response) {
  vector<string> msgs = table.getStockTickers();
  
  for (auto& msg : msgs) {
    auto* data = response->mutable_tickers()->Add();
    data->assign(msg);
  }
  
  return Status::OK;
}