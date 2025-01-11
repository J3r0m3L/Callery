#include "StockAggregatesTableMessage.hpp"

#include <crow.h>
#include <string>

using std::string;
using std::to_string;

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

const int StockAggregatesTableMessage::getTimestamp() const {
    return this->timestamp;
}

const float StockAggregatesTableMessage::getClose() const {
    return this->close;
}

const float StockAggregatesTableMessage::getHigh() const {
    return this->high;
}

const float StockAggregatesTableMessage::getLow() const {
    return this->low;
}

const float StockAggregatesTableMessage::getTransactions() const {
    return this->transactions;
}

const float StockAggregatesTableMessage::getOpen() const {
    return this->open;
}

const float StockAggregatesTableMessage::getVolume() const {
    return this->volume;
}

const float StockAggregatesTableMessage::getVwap() const {
    return this->vwap;
}

StockAggregatesTableMessage::operator crow::json::wvalue() const {
    crow::json::wvalue obj;
    obj["ticker"] = this->getTicker();
    obj["timestamp"] = to_string(this->getTimestamp());
    obj["close"] = this->getClose();
    obj["high"] = this->getHigh();
    obj["low"] = this->getLow();
    obj["transactions"] = this->getTransactions();
    obj["open"] = this->getOpen();
    obj["volume"] = this->getVolume();
    obj["vwap"] = this->getVwap();
    return obj;
}