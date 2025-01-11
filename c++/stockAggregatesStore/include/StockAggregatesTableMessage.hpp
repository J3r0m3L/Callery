#pragma once

#include <crow.h>
#include <string>

using std::string;

class StockAggregatesTableMessage {
private:
    const string ticker;
    const int timestamp;
    const float close;
    const float high; 
    const float low;
    const float transactions;
    const float open;
    const float volume; 
    const float vwap;

public:
    StockAggregatesTableMessage(
        const string& ticker,
        int timestamp,
        float close,
        float high,
        float low,
        float transactions,
        float open,
        float volume,
        float vwap
    );

    const string& getTicker() const;
    const int getTimestamp() const;
    const float getClose() const;
    const float getHigh() const;
    const float getLow() const;
    const float getTransactions() const;
    const float getOpen() const;
    const float getVolume() const;
    const float getVwap() const;

    operator crow::json::wvalue() const;
};