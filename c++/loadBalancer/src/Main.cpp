#include <crow.h>
#include <httplib.h>
#include <sstream>
#include <string>
#include <vector>

using std::ostringstream;
using std::string;
using std::vector;

int main() {
    crow::SimpleApp app;

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

        httplib::Client client(backendUrl, 8080);
        auto jsonBody = crow::json::load(req.body);

        ostringstream osJsonBody;
        osJsonBody << jsonBody;
        CROW_LOG_WARNING << osJsonBody.str();

        auto response = client.Post("/query", osJsonBody.str(), "application/json");

        if (response) {
            return crow::response(response->body);
        }
        ostringstream osErr;
        osErr << response.error();
        return crow::response(osErr.str());
    });

    vector<string> stockAlgorithms = {
        "172.20.0.3" // hard coded for now
    }; 
    int stockAlgorithmsIndex = 0;

    CROW_ROUTE(app, "/stockAlgorithms/dickyFuller").methods("POST"_method)
    ([&stockAlgorithms, &stockAlgorithmsIndex](const crow::request& req) {
        string backendUrl = stockAlgorithms.at(stockAlgorithmsIndex);
        stockAlgorithmsIndex = (stockAlgorithmsIndex + 1) % stockAlgorithms.size();

        httplib::Client client(backendUrl, 8082);
        auto jsonBody = crow::json::load(req.body);

        ostringstream osJsonBody;
        osJsonBody << jsonBody;
        CROW_LOG_WARNING << osJsonBody.str();

        auto response = client.Post("/dickyFuller", osJsonBody.str(), "application/json");

        if (response) {
            return crow::response(response->body);
        }
        ostringstream osErr;
        osErr << response.error();
        return crow::response(osErr.str());
    });

    app.port(8081).run();
}