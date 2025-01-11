#include "WhereClauses.hpp"
#include "ColumnDef.hpp"
#include "ColumnDefTypes.hpp"

#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::stringstream;
using std::vector;

WhereClauses::WhereClauses() {
    this->clauses.push_back({});
}

template <>
void WhereClauses::addWhereEquals(ColumnDef& column, string value) {
    this->assertMatchingTypes(column.getColumnType(), value);
    stringstream ss;
    ss << column.getColumnName() << "=" << "'" << value << "'";
    int i = this->clauses.size() - 1;
    this->clauses.at(i).push_back(ss.str());
}

void WhereClauses::addOrOperator() {
    this->clauses.push_back({});
}

string WhereClauses::build() const {
    if (clauses[0].size() == 0) {
        return "";
    }

    stringstream ss;
    ss << " WHERE "; 

    int lastCol = clauses.size() - 1;

    for (int i = 0; i < lastCol; i++) {

        int lastRow = clauses.at(i).size() - 1;
        for (int j = 0; j < lastRow; j++) {
            ss << clauses.at(i).at(j) << " AND ";
        }
        ss << clauses.at(i).at(lastRow);
        ss << " OR ";
    }

    int lastRow = clauses.at(lastCol).size() - 1;
    for (int j = 0; j < lastRow; j++) {
        ss << clauses.at(lastCol).at(j);
        ss << " AND ";
    }
    ss << clauses.at(lastCol).at(lastRow);
    return ss.str();
}

