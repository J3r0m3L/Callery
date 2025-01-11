#pragma once

#include "ColumnDef.hpp"
#include "WhereClauses.hpp"

#include <optional>
#include <string>
#include <vector>

using std::optional;
using std::string;
using std::vector;

class SqlQueryBuilder {

public:
    SqlQueryBuilder(const string& tableName, const vector<ColumnDef>& columns);
    SqlQueryBuilder& whereClauses(const WhereClauses& whereClauses);
    const char* build() const;

private:
    string tableName_;
    optional<WhereClauses> whereClauses_;
    vector<ColumnDef> columns_;
};
