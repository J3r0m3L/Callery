#include "StockAggregatesTable.hpp"

#include <crow.h>
#include <SqlQueryBuilder.hpp>
#include <iostream>
#include <optional>
#include <utility>
#include <string>
#include <vector>

using std::make_pair;
using std::nullopt;
using std::optional;
using std::pair;
using std::string;
using std::vector;

int main() {

    crow::SimpleApp app;
    StockAggregatesTable table = StockAggregatesTable("StockAggregates", "./service/StockData.db");

    CROW_ROUTE(app, "/query").methods("POST"_method)
    ([&table](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON");
        }
        
        optional<string> ticker;
        optional<pair<int, int>> timestampRange;
        optional<pair<float, float>> closeRange;
        optional<pair<float, float>> highRange;
        optional<pair<float, float>> lowRange;
        optional<pair<float, float>> transactionsRange;
        optional<pair<float, float>> openRange;
        optional<pair<float, float>> volumeRange;
        optional<pair<float, float>> vwapRange;

        if (body.has("ticker")) {
            ticker = body["ticker"].s();
        }
        if (body.has("timestampRange") && body["timestampRange"].t() == crow::json::type::List && body["timestampRange"].size() >= 2) {
            timestampRange = make_pair(body["timestampRange"][0].i(), body["timestampRange"][1].i());
        }
        if (body.has("closeRange") && body["closeRange"].t() == crow::json::type::List && body["closesRange"].size() >= 2) {
            closeRange = make_pair(body["closeRange"][0].d(), body["closeRange"][1].d());
        }
        if (body.has("highRange") && body["highRange"].t() == crow::json::type::List && body["highRange"].size() >= 2) {
            highRange = make_pair(body["highRange"][0].d(), body["highRange"][1].d());
        }
        if (body.has("lowRange") && body["lowRange"].t() == crow::json::type::List && body["lowRange"].size() >= 2) {
            lowRange = make_pair(body["lowRange"][0].d(), body["lowRange"][1].d());
        }
        if (body.has("transactionsRange") && body["transactionsRange"].t() == crow::json::type::List && body["transactionsRange"].size() >= 2) {
            transactionsRange = make_pair(body["transactionsRange"][0].d(), body["transactionsRange"][1].d());
        }
        if (body.has("openRange") && body["openRange"].t() == crow::json::type::List && body["openRange"].size() >= 2) {
            openRange = make_pair(body["openRange"][0].d(), body["openRange"][1].d());
        }
        if (body.has("volumeRange") && body["volumeRange"].t() == crow::json::type::List && body["volumeRange"].size() >= 2) {
            volumeRange = make_pair(body["volumeRange"][0].d(), body["volumeRange"][1].d());
        }
        if (body.has("vwapRange") && body["vwapRange"].t() == crow::json::type::List && body["vwapRange"].size() >= 2) {
            vwapRange = make_pair(body["vwapRange"][0].d(), body["vwapRange"][1].d());
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

        crow::json::wvalue response; 
        response["body"] = crow::json::wvalue::list(msgs.begin(), msgs.end());
        return crow::response(response);
    });


    CROW_ROUTE(app, "/tickers").methods("GET"_method)
    ([&table]() {
        vector<string> msgs = table.getStockTickers();

        crow::json::wvalue response; 
        response["body"] = crow::json::wvalue::list(msgs.begin(), msgs.end());
        return crow::response(response);
    });


    app.port(8080).run();
}