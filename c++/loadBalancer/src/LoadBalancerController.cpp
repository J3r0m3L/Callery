#include "proto/StockAggregatesStoreService.grpc.pb.h"
#include "proto/StockAggregatesStoreService.pb.h"
#include "proto/StockAlgorithmsService.grpc.pb.h"
#include "proto/StockAlgorithmsService.pb.h"

#include <crow.h>
#include <crow/middlewares/cors.h>
#include <google/protobuf/util/json_util.h>
#include <grpcpp/grpcpp.h>
#include <memory>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using SasPkg::SasTableQuery;
using SasPkg::SasTableMsgs;
using SasPkg::SasTickers;
using SasPkg::StockAggregatesStoreService;
using SaPkg::SaDickyFullerRequest;
using SaPkg::SaDickyFullerResponse;
using SaPkg::StockAlgorithmsService;
using std::make_pair;
using std::optional;
using std::ostringstream;
using std::pair;
using std::regex;
using std::regex_match;
using std::stoll;
using std::string;
using std::shared_ptr;
using std::vector;

int main() {
    crow::App<crow::CORSHandler> app;

    // todo: implement a reader as this interact across the docker network and the docker network is non-deterministic
    // consider moving boiler this to method or class
    vector<string> stockAggregateStores = {
        "172.20.0.2" // hard coded for now
    }; 
    int stockAggregatesStoreIndex = 0;

    CROW_ROUTE(app, "/stockAggregatesStore/query").methods("POST"_method)
    ([&stockAggregateStores, &stockAggregatesStoreIndex](const crow::request& req) {
        string backendUrl = stockAggregateStores.at(stockAggregatesStoreIndex);
        stockAggregatesStoreIndex = (stockAggregatesStoreIndex + 1) % stockAggregateStores.size();

        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON");
        }

        ClientContext context;
        SasTableQuery request;
        SasTableMsgs response; 
        if (body.has("ticker")) {
            string ticker = body["ticker"].s();
            regex isAlphaRegex("^[a-zA-Z]+$");
            if (!regex_match(ticker, isAlphaRegex)) {
                return crow::response(400, "Invalid JSON");
            }
            request.set_ticker(ticker);
        }
        if (body.has("timestampRange") && body["timestampRange"].t() == crow::json::type::List) {
            for (auto& it : body["timestampRange"]) {
                request.add_timestamprange(stoll(it.s()));
            }
        }
        if (body.has("closeRange") && body["closeRange"].t() == crow::json::type::List) {
            for (auto& it : body["closeRange"]) {
                request.add_closerange(it.d());
            }
        }
        if (body.has("highRange") && body["highRange"].t() == crow::json::type::List) {
            for (auto& it : body["highRange"]) {
                request.add_highrange(it.d());
            }
        }
        if (body.has("lowRange") && body["lowRange"].t() == crow::json::type::List) {
            for (auto& it : body["lowRange"]) {
                request.add_lowrange(it.d());
            }
        }
        if (body.has("transactionsRange") && body["transactionsRange"].t() == crow::json::type::List) {
            for (auto& it : body["transactionsRange"]) {
                request.add_transactionsrange(it.d());
            }
        }
        if (body.has("openRange") && body["openRange"].t() == crow::json::type::List) {
            for (auto& it : body["openRange"]) {
                request.add_openrange(it.d());
            }
        }
        if (body.has("volumeRange") && body["volumeRange"].t() == crow::json::type::List) {
            for (auto& it : body["volumeRange"]) {
                request.add_volumerange(it.d());
            }
        }
        if (body.has("vwapRange") && body["vwapRange"].t() == crow::json::type::List) {
            for (auto& it : body["vwapRange"]) {
                request.add_vwaprange(it.d());
            }
        }

        shared_ptr<Channel> channel = grpc::CreateChannel(backendUrl + ":8080", grpc::InsecureChannelCredentials());
        StockAggregatesStoreService::Stub stub(channel);

        Status status = stub.queryStockAggregatesTable(&context, request, &response);
        if (status.ok()) {
            string json_string;
            static_cast<void>(google::protobuf::util::MessageToJsonString(response, &json_string));
            crow::response res(json_string);
            res.set_header("Content-Type", "application/json");
            return res;
        }

        return crow::response(500, "Error running queryStockAggregatesTable");
    });

    CROW_ROUTE(app, "/stockAggregatesStore/tickers").methods("GET"_method)
    ([&stockAggregateStores, &stockAggregatesStoreIndex]() {
        string backendUrl = stockAggregateStores.at(stockAggregatesStoreIndex);
        stockAggregatesStoreIndex = (stockAggregatesStoreIndex + 1) % stockAggregateStores.size();

        ClientContext context;
        google::protobuf::Empty request;
        SasTickers response; 

        shared_ptr<Channel> channel = grpc::CreateChannel(backendUrl + ":8080", grpc::InsecureChannelCredentials());
        StockAggregatesStoreService::Stub stub(channel);

        Status status = stub.getStockTickers(&context, request, &response);
        if (status.ok()) {
            string json_string;
            static_cast<void>(google::protobuf::util::MessageToJsonString(response, &json_string));
            crow::response res(json_string);
            res.set_header("Content-Type", "application/json");
            return res;
        }

        return crow::response(500, "Error running getStockTickers");
    });

    vector<string> stockAlgorithms = {
        "172.20.0.3" // hard coded for now
    }; 
    int stockAlgorithmsIndex = 0;

    CROW_ROUTE(app, "/stockAlgorithms/dickyFuller").methods("POST"_method)
    ([&stockAggregateStores, &stockAggregatesStoreIndex, stockAlgorithms, &stockAlgorithmsIndex](const crow::request& req) {
        string sasBackendUrl = stockAggregateStores.at(stockAggregatesStoreIndex);
        stockAggregatesStoreIndex = (stockAggregatesStoreIndex + 1) % stockAggregateStores.size();

        // todo: add lag parameter, for now defaults to 1
        auto body = crow::json::load(req.body);

        bool hasTicker = body.has("ticker") && body["ticker"].t() == crow::json::type::String;
        if (!body || !hasTicker) {
            return crow::response(400, "Invalid JSON");
        } 
        
        string ticker = body["ticker"].s();
        regex isAlphaRegex("^[a-zA-Z]+$");
        if (!regex_match(ticker, isAlphaRegex)) {
            return crow::response(400, "Invalid JSON");
        }
        
        ClientContext sasClient;
        SasTableQuery sasRequest;
        SasTableMsgs sasResponse; 

        sasRequest.set_ticker(body["ticker"].s());

        shared_ptr<Channel> sasChannel = grpc::CreateChannel(sasBackendUrl + ":8080", grpc::InsecureChannelCredentials());
        StockAggregatesStoreService::Stub sasStub(sasChannel);

        Status sasStatus = sasStub.queryStockAggregatesTable(&sasClient, sasRequest, &sasResponse);
        if (!sasStatus.ok()) {
            ostringstream os;
            os << "Failed to retrieve stock data for " << body["ticker"].s();
            return crow::response(500, os.str());
        }

        string saBackendUrl = stockAlgorithms.at(stockAlgorithmsIndex);
        stockAlgorithmsIndex = (stockAlgorithmsIndex + 1) % stockAlgorithms.size();

        ClientContext saContext;
        SaDickyFullerRequest saRequest;
        SaDickyFullerResponse saResponse;

        for (auto& it: *sasResponse.mutable_msgs()) {
            saRequest.add_stockprices(it.high());
        }
        
        shared_ptr<Channel> saChannel = grpc::CreateChannel(saBackendUrl + ":8082", grpc::InsecureChannelCredentials());
        StockAlgorithmsService::Stub saStub(saChannel);

        Status saStatus = saStub.dickyFullerTest(&saContext, saRequest, &saResponse);
        if (saStatus.ok()) {
            string json_string;
            static_cast<void>(google::protobuf::util::MessageToJsonString(saResponse, &json_string));
            crow::response res(json_string);
            res.set_header("Content-Type", "application/json");
            return res;
        }

        return crow::response(500, "Error running dickyFullerTest");
    });

    app.port(8081).run();
}