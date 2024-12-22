#pragma once

#include "ColumnDef.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

class WhereClauses {

private:
    vector<vector<string>> clauses;

    // SQLite converts type like 'AB' to 0 when it should throw an error.
    template<typename T>
    void assertMatchingTypes(ColumnDefTypes& type, T value);

public:
    WhereClauses();

    template<typename T>
    void addWhereEquals(ColumnDef& column, T value);

    template<typename T>
    void addWhereLessThan(ColumnDef& column, T value);

    template<typename T>
    void addWhereLessThanOrEquals(ColumnDef& column, T value);

    template<typename T> 
    void addWhereGreaterThan(ColumnDef& column, T value);

    template<typename T>
    void addWhereGreaterThanOrEquals(ColumnDef& column, T value);

    void addOrOperator();

    string build() const;
};