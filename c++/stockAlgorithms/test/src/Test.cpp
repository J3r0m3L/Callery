#include "DickyFuller.hpp"

#include <cmath>
#include <cassert>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

using nlohmann::json;
using std::abs;
using std::ifstream;
using std::vector;


bool isClose(float number1, float number2, float epsilon = 1e-3) {
    return abs(number1 - number2) < epsilon;
}

int main() {
    ifstream file("./service/test/testCases/dickyFullerTest.json");
    json jsonData = json::parse(file);
    
    vector<float> stockPrices;
    if (jsonData.contains("stockPrices") && jsonData["stockPrices"].is_array()) {
        stockPrices = jsonData["stockPrices"].get<vector<float>>();
    }
    
    float tStat;
    if (jsonData.contains("t-stat") && jsonData["t-stat"].is_number_float()) {
        tStat = jsonData["t-stat"].get<float>();
    }

    int maxLag;
    if (jsonData.contains("maxLag") && jsonData["maxLag"].is_number_integer()) {
        maxLag = jsonData["maxLag"].get<int>();
    }

    assert(isClose(DickyFuller::testWithTrendAndConstant(stockPrices, maxLag), tStat));
}