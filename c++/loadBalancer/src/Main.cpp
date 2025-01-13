#include <crow.h>
#include <crow/json.h>
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
    vector<string> stockAggregateStores = {
        "172.20.0.2" // hard coded for now
    }; 
    int currentServerIndex = 0;

    CROW_ROUTE(app, "/stockAggregatesStore/query").methods("POST"_method)
    ([&stockAggregateStores, &currentServerIndex](const crow::request& req) {
        string backendUrl = stockAggregateStores.at(currentServerIndex);
        currentServerIndex = (currentServerIndex + 1) % stockAggregateStores.size();

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

    app.port(8081).run();
}