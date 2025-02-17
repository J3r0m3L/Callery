#pragma once

#include "StockAggregatesTableMessage.hpp"
#include "StockAggregatesTableQuery.hpp"

#include <ColumnDef.hpp>
#include <ColumnDefTypes.hpp>

#include <string>
#include <vector>

using std::string;
using std::vector;

class StockAggregatesTable {

private:
    string tablename_;
    char* directory_;
    ColumnDef TICKER = ColumnDef("ticker", ColumnDefTypes::StringDef);
    ColumnDef TIMESTAMP = ColumnDef("timestamp", ColumnDefTypes::LongDef);
    ColumnDef CLOSE = ColumnDef("close", ColumnDefTypes::FloatDef);
    ColumnDef HIGH = ColumnDef("high", ColumnDefTypes::FloatDef);
    ColumnDef LOW = ColumnDef("low", ColumnDefTypes::FloatDef);
    ColumnDef TRANSACTIONS = ColumnDef("transactions", ColumnDefTypes::FloatDef);
    ColumnDef OPEN = ColumnDef("open", ColumnDefTypes::FloatDef);
    ColumnDef VOLUME = ColumnDef("volume", ColumnDefTypes::FloatDef);
    ColumnDef VWAP = ColumnDef("vwap", ColumnDefTypes::FloatDef);

public:
    StockAggregatesTable(string tablename, char* directory);
    ~StockAggregatesTable();
    vector<StockAggregatesTableMessage> queryStockAggregatesTable(StockAggregatesTableQuery query);
    vector<string> getStockTickers();
};