#include "StockAggregatesTableQuery.hpp"

#include <optional>
#include <string>
#include <utility>

using std::optional;
using std::pair;
using std::string;

StockAggregatesTableQuery::StockAggregatesTableQuery(
    const optional<string> ticker,
    const optional<pair<int, int>> timestampRange,
    const optional<pair<float, float>> closeRange,
    const optional<pair<float, float>> highRange,
    const optional<pair<float, float>> lowRange,
    const optional<pair<float, float>> transactionsRange,
    const optional<pair<float, float>> openRange,
    const optional<pair<float, float>> volumeRange,
    const optional<pair<float, float>> vwapRange
) : 
ticker(ticker),
timestampRange(timestampRange),
closeRange(closeRange),
highRange(highRange),
lowRange(lowRange),
transactionsRange(transactionsRange),
openRange(openRange),
volumeRange(volumeRange),
vwapRange(vwapRange) {}

const optional<string>& StockAggregatesTableQuery::getTicker() const {
    return this->ticker;
};

const optional<pair<int, int>>& StockAggregatesTableQuery::getTimestampRange() const {
    return this->timestampRange;
};

const optional<pair<float, float>>& StockAggregatesTableQuery::getCloseRange() const {
    return this->closeRange;
};

const optional<pair<float, float>>& StockAggregatesTableQuery::getHighRange() const {
    return this->highRange;
};

const optional<pair<float, float>>& StockAggregatesTableQuery::getLowRange() const {
    return this->lowRange;
};

const optional<pair<float, float>>& StockAggregatesTableQuery::getTransactionRange() const {
    return this->transactionsRange;
};

const optional<pair<float, float>>& StockAggregatesTableQuery::getOpenRange() const {
    return this->openRange;
};

const optional<pair<float, float>>& StockAggregatesTableQuery::getVolumeRange() const {
    return this->volumeRange;
};

const optional<pair<float, float>>& StockAggregatesTableQuery::getVwapRange() const {
    return this->vwapRange;
};