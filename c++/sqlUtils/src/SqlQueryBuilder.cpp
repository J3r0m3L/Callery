#include "SqlQueryBuilder.h"

#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::stringstream;
using std::vector;

SqlQueryBuilder::SqlQueryBuilder(const string& tableName, const vector<ColumnDef>& columns) {
    _tableName = tableName;
    _columns = columns;
}

SqlQueryBuilder& SqlQueryBuilder::whereClauses(const WhereClauses& whereClauses) {
    _whereClauses = whereClauses;
    return *this;
}

const char* SqlQueryBuilder::build() const {
    stringstream ss;
    ss << "SELECT ";

    for (int i = 0; i < _columns.size() - 1; i++) {
        ss << _columns.at(i).getColumnName() + ", ";
    }
    ss << _columns.at(_columns.size() - 1).getColumnName();
    ss << " FROM" << _tableName + " ";

    if (_whereClauses.has_value()) {
        ss << _whereClauses->build();
    }
    ss << ";";
    const string& tmp = ss.str();
    return tmp.c_str(); 
}