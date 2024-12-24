#pragma once

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
    int getTimestamp();
    float getClose();
    float getHigh();
    float getLow();
    float getTransactions();
    float getOpen();
    float getVolume();
    float getVwap();
};