#include "ColumnDef.hpp"
#include "ColumnDefTypes.hpp"
#include <string>

using std::string;

ColumnDef::ColumnDef(
    string columnName, 
    ColumnDefTypes columnType
) : 
columnName(columnName), 
columnType(columnType) {}

const string& ColumnDef::getColumnName() const {
    return this->columnName;
}

const ColumnDefTypes& ColumnDef::getColumnType() const {
    return this->columnType;
}

