#include "StockAggregatesTableMessage.h"

#include <string>

using std::string;

StockAggregatesTableMessage::StockAggregatesTableMessage (
    const string& ticker,
    int timestamp,
    float close,
    float high,
    float low,
    float transactions,
    float open,
    float volume, 
    float vwap
) : 
ticker(ticker),
timestamp(timestamp),
close(close),
high(high),
low(low),
transactions(transactions),
open(open),
volume(volume),
vwap(vwap) {}

const string& StockAggregatesTableMessage::getTicker() const {
    return this->ticker;
}

int StockAggregatesTableMessage::getTimestamp() {
    return this->timestamp;
}

float StockAggregatesTableMessage::getClose() {
    return this->close;
}

float StockAggregatesTableMessage::getHigh() {
    return this->high;
}

float StockAggregatesTableMessage::getLow() {
    return this->low;
}

float StockAggregatesTableMessage::getTransactions() {
    return this->transactions;
}

float StockAggregatesTableMessage::getOpen() {
    return this->open;
}

float StockAggregatesTableMessage::getVolume() {
    return this->volume;
}

float StockAggregatesTableMessage::getVwap() {
    return this->vwap;
}