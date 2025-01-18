#include "SqlQueryBuilder.hpp"

#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::ostringstream;
using std::vector;

SqlQueryBuilder::SqlQueryBuilder(const string& tableName, const vector<ColumnDef>& columns) {
    tableName_ = tableName;
    columns_ = columns;
}

SqlQueryBuilder& SqlQueryBuilder::whereClauses(const WhereClauses& whereClauses) {
    whereClauses_ = whereClauses;
    return *this;
}

SqlQueryBuilder& SqlQueryBuilder::distinct() {
    distinct_ = true;
    return *this;
}

const string SqlQueryBuilder::build() const {
    ostringstream ss;
    ss << "SELECT ";

    if (distinct_) ss << "DISTINCT ";

    for (int i = 0; i < columns_.size() - 1; i++) {
        ss << columns_.at(i).getColumnName() << ", ";
    }
    ss << columns_.at(columns_.size() - 1).getColumnName();
    ss << " FROM " << tableName_;

    if (whereClauses_.has_value()) {
        ss << whereClauses_->build();
    }
    ss << ";";
    return ss.str();
}
    