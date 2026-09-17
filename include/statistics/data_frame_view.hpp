#pragma once

#include "statistics/data_frame.hpp"

namespace statistics
{
    class DataFrameView {
    public:
        DataFrameView(const DataFrame& data, const TimeRange& range);

    private:
        const DataFrame& m_data;
        const TimeRange m_range;

        std::unordered_map<std::string, std::span<const JsonDataEntry>> m_songRanges;
    };
    
} // namespace statistics
