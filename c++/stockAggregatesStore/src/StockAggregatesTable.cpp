#include "StockAggregatesTable.hpp"

#include <SqlQueryBuilder.hpp>
#include <WhereClauses.hpp>

#include <crow.h>
#include <vector>
#include <sqlite3.h>

using std::vector;
using std::stoi;
using std::stof;

StockAggregatesTable::StockAggregatesTable(string tablename): _tablename(tablename) {};

static int buildSATMMessages(void* data, int argc, char** argv, char** azColNmae) {
    vector<StockAggregatesTableMessage>* msgs = static_cast<vector<StockAggregatesTableMessage>*>(data);

    StockAggregatesTableMessage msg = StockAggregatesTableMessage(
        argv[0],
        stoi(argv[1]),
        stof(argv[2]),
        stof(argv[3]),
        stof(argv[4]),
        stof(argv[5]),
        stof(argv[6]),
        stof(argv[7]),
        stof(argv[8])
    );

    msgs->push_back(msg);
    return 0; 
}

vector<StockAggregatesTableMessage> StockAggregatesTable::queryStockAggregatesTable(StockAggregatesTableQuery query) {

    vector<ColumnDef> columns = {
        this->TICKER,
        this->TIMESTAMP,
        this->CLOSE,
        this->HIGH,
        this->LOW,
        this->TRANSACTIONS,
        this->OPEN,
        this->VOLUME,
        this->VWAP
    };

    SqlQueryBuilder builder = SqlQueryBuilder(this->_tablename, columns);
    WhereClauses whereClauses = WhereClauses();

    if (query.getTicker().has_value()) whereClauses.addWhereEquals(this->TICKER, *query.getTicker());

    if (query.getTimestampRange().has_value()) {
        whereClauses.addWhereGreaterThanOrEquals(this->TIMESTAMP, query.getTimestampRange()->first);
        whereClauses.addWhereLessThanOrEquals(this->TIMESTAMP, query.getTimestampRange()->second);
    }

    if (query.getCloseRange().has_value()) {
        whereClauses.addWhereGreaterThanOrEquals(this->CLOSE, query.getCloseRange()->first);
        whereClauses.addWhereLessThanOrEquals(this->CLOSE, query.getCloseRange()->second);
    }

    if (query.getHighRange().has_value()) {
        whereClauses.addWhereGreaterThanOrEquals(this->CLOSE, query.getHighRange()->first);
        whereClauses.addWhereLessThanOrEquals(this->CLOSE, query.getHighRange()->second);
    }

    if (query.getLowRange().has_value()) {
        whereClauses.addWhereGreaterThanOrEquals(this->CLOSE, query.getLowRange()->first);
        whereClauses.addWhereLessThanOrEquals(this->CLOSE, query.getLowRange()->second);
    }

    if (query.getTransactionRange().has_value()) {
        whereClauses.addWhereGreaterThanOrEquals(this->TRANSACTIONS, query.getTransactionRange()->first);
        whereClauses.addWhereLessThanOrEquals(this->TRANSACTIONS, query.getTransactionRange()->second);
    }

    if (query.getOpenRange().has_value()) {
        whereClauses.addWhereGreaterThanOrEquals(this->TRANSACTIONS, query.getOpenRange()->first);
        whereClauses.addWhereLessThanOrEquals(this->TRANSACTIONS, query.getOpenRange()->second);
    }

    if (query.getVolumeRange().has_value()) {
        whereClauses.addWhereGreaterThanOrEquals(this->VOLUME, query.getVolumeRange()->first);
        whereClauses.addWhereLessThanOrEquals(this->VOLUME, query.getVolumeRange()->second);
    }

    if (query.getVwapRange().has_value()) {
        whereClauses.addWhereGreaterThanOrEquals(this->VWAP, query.getVwapRange()->first);
        whereClauses.addWhereLessThanOrEquals(this->VWAP, query.getVwapRange()->second);
    }

    sqlite3* DB;
    int exit = sqlite3_open("stock.db", &DB);
    
    vector<StockAggregatesTableMessage> msgs; 
    char* errorMessage;
    sqlite3_exec(DB, builder.whereClauses(whereClauses).build(), buildSATMMessages, &msgs, &errorMessage);

    sqlite3_close(DB);
    delete errorMessage;
    return msgs;
}
