#pragma once

#include <optional>
#include <string>
#include <utility>

using std::optional;
using std::pair;
using std::string;

class StockAggregatesTableQuery {
private:
    const optional<string> ticker;
    const optional<pair<long long, long long>> timestampRange;
    const optional<pair<float, float>> closeRange;
    const optional<pair<float, float>> highRange;
    const optional<pair<float, float>> lowRange;
    const optional<pair<float, float>> transactionsRange;
    const optional<pair<float, float>> openRange;
    const optional<pair<float, float>> volumeRange;
    const optional<pair<float, float>> vwapRange;

public:
    StockAggregatesTableQuery(
        const optional<string> ticker,
        const optional<pair<long long, long long>> timestampRange,
        const optional<pair<float, float>> closeRange,
        const optional<pair<float, float>> highRange,
        const optional<pair<float, float>> lowRange,
        const optional<pair<float, float>> transactionRange,
        const optional<pair<float, float>> openRange,
        const optional<pair<float, float>> volumeRange,
        const optional<pair<float, float>> vwapRange
    );

    const optional<string>& getTicker() const;
    const optional<pair<long long, long long>>& getTimestampRange() const;
    const optional<pair<float, float>>& getCloseRange() const;
    const optional<pair<float, float>>& getHighRange() const;
    const optional<pair<float, float>>& getLowRange() const;
    const optional<pair<float, float>>& getTransactionRange() const;
    const optional<pair<float, float>>& getOpenRange() const;
    const optional<pair<float, float>>& getVolumeRange() const;
    const optional<pair<float, float>>& getVwapRange() const;
};