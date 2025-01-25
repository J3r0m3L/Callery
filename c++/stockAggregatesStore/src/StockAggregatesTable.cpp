#include "StockAggregatesTable.hpp"
#include "StockAggregatesTableMessage.hpp"

#include <SqlQueryBuilder.hpp>
#include <WhereClauses.hpp>

#include <crow.h>
#include <vector>
#include <sqlite3.h>

using std::vector;
using std::stoi;
using std::stof;

StockAggregatesTable::StockAggregatesTable(string tablename, char* directory): tablename_(tablename), directory_(directory) {
    sqlite3* DB;
    int errorMsg = 0;
    if ((errorMsg = sqlite3_open_v2(directory_, &DB, SQLITE_OPEN_READONLY, NULL)) == SQLITE_OK) {
        CROW_LOG_INFO << "Database Connected";
    } else {
        CROW_LOG_WARNING << "Database Failed To Connect: " << errorMsg;
    }
    sqlite3_close_v2(DB);
}

StockAggregatesTable::~StockAggregatesTable() { delete this->directory_; }

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
    
    SqlQueryBuilder builder = SqlQueryBuilder(this->tablename_, columns);
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
    sqlite3_stmt* stmt;
    int errMsg = 0;

    vector<StockAggregatesTableMessage> msgs = {};

    if ((errMsg = sqlite3_open_v2(directory_, &DB, SQLITE_OPEN_READONLY, NULL)) == SQLITE_OK) {
        sqlite3_prepare_v2(DB, builder.whereClauses(whereClauses).build().c_str(), -1, &stmt, NULL);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            msgs.emplace_back(StockAggregatesTableMessage(
                string((char*) sqlite3_column_text(stmt, 0)),
                sqlite3_column_int64(stmt, 1),
                (float) sqlite3_column_double(stmt, 2),
                (float) sqlite3_column_double(stmt, 3),
                (float) sqlite3_column_double(stmt, 4),
                (float) sqlite3_column_double(stmt, 5),
                (float) sqlite3_column_double(stmt, 6),
                (float) sqlite3_column_double(stmt, 7),
                (float) sqlite3_column_double(stmt, 8)
            ));
        }
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
    } else {
        CROW_LOG_WARNING << "Database Failed To Connect: " << errMsg;
    }

    return msgs;
}

vector<string> StockAggregatesTable::getStockTickers() {
    vector<ColumnDef> columns = { this->TICKER };
    SqlQueryBuilder builder = SqlQueryBuilder(this->tablename_, columns);

    sqlite3* DB;
    sqlite3_stmt* stmt;
    int errMsg = 0;

    vector<string> msgs = {};

    if ((errMsg = sqlite3_open_v2(directory_, &DB, SQLITE_OPEN_READONLY, NULL)) == SQLITE_OK) {
        sqlite3_prepare_v2(DB, builder.distinct().build().c_str(), -1, &stmt, NULL);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            msgs.emplace_back(string((char*) sqlite3_column_text(stmt, 0)));
        }
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
    } else {
        CROW_LOG_WARNING << "Database Failed To Connect: " << errMsg;
    }

    return msgs;
}
