#include <crow.h>
#include <optional>


using std::optional;

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/dickyFuller").methods("POST"_method)
    ([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON");
        }

        float res = 0.0;
        if (body.has("stockPrices") && body["stockPrices"].t() == crow::json::type::List) {
            // forward to method
        }

        crow::json::wvalue response;
        response["body"] = res;
        return crow::response(response);
    });

    app.port(8082).run();
}