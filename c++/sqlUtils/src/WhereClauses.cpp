#include "WhereClauses.h"
#include "ColumnDef.h"
#include "ColumnDefTypes.h"

#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::stringstream;
using std::vector;

WhereClauses::WhereClauses() {
    this->clauses.push_back({});
}

void WhereClauses::addOrOperator() {
    this->clauses.push_back({});
}

string WhereClauses::build() const {
    stringstream ss;
    ss << "WHERE "; 

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

