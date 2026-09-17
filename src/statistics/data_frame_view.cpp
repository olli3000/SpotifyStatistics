#include "statistics/data_frame_view.hpp"

namespace statistics
{
    void printTime(std::chrono::system_clock::time_point time)
    {
        std::time_t t = std::chrono::system_clock::to_time_t(time);

        std::cout << std::put_time(
            std::gmtime(&t),
            "%Y-%m-%d %H:%M:%S"
        );
    }

    DataFrameView::DataFrameView(const DataFrame& data, const TimeRange& range) : m_data(data), m_range(range) {
        for (auto& [ID, history] : data._songData) {
            m_songRanges.emplace(ID, history.getSpanFromTimeRange(range));
            // if (ID == "61ZM92T2zaXIVsqncThQzC") {
                
            // }
        }
    }
    
} // namespace statistics
