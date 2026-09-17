#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <span>

#include "json_data_entry.hpp"
#include "statistics/util.hpp"

namespace statistics
{
    class SongHistory {
    public:
        SongHistory(JsonDataEntry&& firstInstance);

        void addInstance(JsonDataEntry&& instance);

        std::span<const JsonDataEntry> getSpanFromTimeRange(const TimeRange& range) const;
        
        std::string_view getID() const;
        std::string_view getTitle() const;
        std::string_view getArtist() const;
        std::string_view getAlbum() const;
        size_t size() const;
        int total() const;
        
        double calcRatioSkipped();
        
        std::string toString();

    private:
        friend class DataFrame;
        friend class DataFrameView;

        std::string _id;
        std::vector<JsonDataEntry> _instances;

        int _min = -1;
        int _max = -1;
        int _total = 0;
        double _avg = 0.0;

        void updateMinMaxTotalAvg(JsonDataEntry& instance);
    };
    
} // namespace statistics
