#pragma once

#include <optional>
#include <unordered_map>
#include <iostream>

#include "statistics/data_frame.hpp"
#include "statistics/data_frame_view.hpp"
#include "statistics/util.hpp"

namespace statistics
{
    class DataFramePool {
    public:
        DataFramePool() {}

        void setData(DataFrame&& data) {
            m_data = std::move(data);
        }

        DataFrameView& getDataFrameViewForRange(const TimeRange& range) {
            if (!m_data.has_value()) {
                throw std::runtime_error("Data frame pool used before data exists");
            }

            if (m_pool.contains(range)) {
                return m_pool.at(range);
            } else {
                auto [it, inserted] = m_pool.emplace(range, DataFrameView{m_data.value(), range});
                return it->second;
            }
        }

        DataFrameView& getDataFrameViewForRange() {
            if (!m_data.has_value()) {
                throw std::runtime_error("Data frame pool used before data exists");
            }

            return getDataFrameViewForRange(m_data.value().getFullTimeRange());
        }

        TimeRange getFullTimeRange() const {
            if (!m_data.has_value()) {
                throw std::runtime_error("Data frame pool used before data exists");
            }

            return m_data.value().getFullTimeRange();
        }

    private:
        std::optional<DataFrame> m_data;
        std::unordered_map<TimeRange, DataFrameView> m_pool;
    };

} // namespace statistics
