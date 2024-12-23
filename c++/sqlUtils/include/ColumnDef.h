#pragma once

#include "ColumnDefTypes.h"
#include <string> 

using std::string;

class ColumnDef {

private:
    string columnName;
    ColumnDefTypes columnType;

public:
    ColumnDef(string columnName, ColumnDefTypes columnType);
    const string& getColumnName() const;
    const ColumnDefTypes& getColumnType() const;

};