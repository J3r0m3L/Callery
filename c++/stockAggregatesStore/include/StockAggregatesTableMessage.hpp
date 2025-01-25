#pragma once

#include <string>

using std::string;

class StockAggregatesTableMessage {
private:
    const string ticker;
    const long long timestamp;
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
        long long timestamp,
        float close,
        float high,
        float low,
        float transactions,
        float open,
        float volume,
        float vwap
    );

    const string& getTicker() const;
    const long long getTimestamp() const;
    const float getClose() const;
    const float getHigh() const;
    const float getLow() const;
    const float getTransactions() const;
    const float getOpen() const;
    const float getVolume() const;
    const float getVwap() const;
};