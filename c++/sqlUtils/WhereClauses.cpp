#include "WhereClauses.h"
#include "ColumnDef.h"
#include "ColumnDefTypes.cpp"

#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

using std::is_same;
using std::runtime_error;
using std::string;
using std::stringstream;
using std::vector;

template<typename T>
void WhereClauses::assertMatchingTypes(ColumnDefTypes& type, T value) {
    bool stringMatch = type == ColumnDefTypes::StringDef && is_same<T, string>::value;
    bool floatMatch = type == ColumnDefTypes::FloatDef && is_same<T, float>::value;
    bool intMatch = type == ColumnDefTypes::IntegerDef && is_same<T, int>::value;

    if (!stringMatch && !floatMatch && !intMatch) {
        throw runtime_error("Value Type does not match Column Type")
    }
}

WhereClauses::WhereClauses() {
    this->clauses.push_back({});
}

template<typename T>
void WhereClauses::addWhereEquals(ColumnDef& column, T value) {
    assertMatchingTypes(column.getColumnType(), value);
    stringstream ss;
    ss << column.getColumnName() << "=" << value;
    int i = this->clauses.size() - 1;
    this->clauses.at(i).push_back(ss.str());
}

template<typename T>
void WhereClauses::addWhereLessThan(ColumnDef& column, T value) {
    assertMatchingTypes(column.getColumnType(), value);
    stringstream ss;
    ss << column.getColumnName() << "<" << value;
    int i =this->clauses.size() - 1;
    this->clauses.at(i).push_back(ss.str());
}

template<typename T>
void WhereClauses::addWhereLessThanOrEquals(ColumnDef& column, T value) {
    assertMatchingTypes(column.getColumnType(), value);
    stringstream ss;
    ss << column.getColumnName() << "<=" << value;
    int i =this->clauses.size() - 1;
    this->clauses.at(i).push_back(ss.str());
}

template<typename T>
void WhereClauses::addWhereGreaterThan(ColumnDef& column, T value) {
    assertMatchingTypes(column.getColumnType(), value);
    stringstream ss;
    ss << column.getColumnName() << ">" << value;
    int i =this->clauses.size() - 1;
    this->clauses.at(i).push_back(ss.str());
}

template<typename T>
void WhereClauses::addWhereGreaterThanOrEquals(ColumnDef& column, T value) {
    assertMatchingTypes(column.getColumnType(), value);
    stringstream ss;
    ss << column.getColumnName() << ">=" << value;
    int i =this->clauses.size() - 1;
    this->clauses.at(i).push_back(ss.str());
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

