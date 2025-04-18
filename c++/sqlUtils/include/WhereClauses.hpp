#pragma once

#include "ColumnDef.hpp"

#include <sstream>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <vector>

using std::enable_if_t;
using std::is_same;
using std::is_same_v;
using std::runtime_error;
using std::string;
using std::stringstream;
using std::vector;

class WhereClauses {

private:
    vector<vector<string>> clauses;

    // SQLite converts type like 'AB' to 0 when it should throw an error.
    template<typename T>
    void assertMatchingTypes(const ColumnDefTypes& type, T value) {
        bool stringMatch = type == ColumnDefTypes::StringDef && is_same<T, string>::value;
        bool floatMatch = type == ColumnDefTypes::FloatDef && is_same<T, float>::value;
        bool intMatch = type == ColumnDefTypes::IntegerDef && is_same<T, int>::value;
        bool longMatch = type == ColumnDefTypes::LongDef && is_same<T, long long>::value;

        if (!stringMatch && !floatMatch && !intMatch) {
            throw runtime_error("Value Type does not match Column Type");
        }
    }

public:
    WhereClauses();

    template<typename T>
    void addWhereEquals(ColumnDef& column, T value) {
        this->assertMatchingTypes(column.getColumnType(), value);
        stringstream ss;
        ss << column.getColumnName() << "=" << value;
        int i = this->clauses.size() - 1;
        this->clauses.at(i).push_back(ss.str());
    }

    template<typename T, typename = enable_if_t<!is_same_v<T, string>>>
    void addWhereLessThan(ColumnDef& column, T value) {
        this->assertMatchingTypes(column.getColumnType(), value);
        stringstream ss;
        ss << column.getColumnName() << "<" << value;
        int i =this->clauses.size() - 1;
        this->clauses.at(i).push_back(ss.str());
    }

    template<typename T, typename = enable_if_t<!is_same_v<T, string>>>
    void addWhereLessThanOrEquals(ColumnDef& column, T value) {
        this->assertMatchingTypes(column.getColumnType(), value);
        stringstream ss;
        ss << column.getColumnName() << "<=" << value;
        int i =this->clauses.size() - 1;
        this->clauses.at(i).push_back(ss.str());
    }

    template<typename T, typename = enable_if_t<!is_same_v<T, string>>>
    void addWhereGreaterThan(ColumnDef& column, T value) {
        this->assertMatchingTypes(column.getColumnType(), value);
        stringstream ss;
        ss << column.getColumnName() << ">" << value;
        int i =this->clauses.size() - 1;
        this->clauses.at(i).push_back(ss.str());
    }
    
    template<typename T, typename = enable_if_t<!is_same_v<T, string>>>
    void addWhereGreaterThanOrEquals(ColumnDef& column, T value) {
        this->assertMatchingTypes(column.getColumnType(), value);
        stringstream ss;
        ss << column.getColumnName() << ">=" << value;
        int i =this->clauses.size() - 1;
        this->clauses.at(i).push_back(ss.str());
    }

    void addOrOperator();

    string build() const;
};