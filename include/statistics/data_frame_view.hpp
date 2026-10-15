#pragma once

#include "statistics/data_frame.hpp"

namespace statistics
{
    class DataFrameView {
    public:
        DataFrameView(const DataFrame& data) : DataFrameView(data, data.getFullTimeRange()) {}
        DataFrameView(const DataFrame& data, const TimeRange& range);

        int getNumberOfSongs() const;
        int getNumberOfArtists() const;
        long getTotalStreamingTime() const;

        std::vector<SongRankingEntry> getSongsRanked() const;
        std::vector<ListeningTimeRankingEntry> getArtistsRanked() const;
        std::vector<ListeningTimeRankingEntry> getAlbumsRanked() const;

    private:
        const DataFrame& m_data;
        const TimeRange m_range;

        std::unordered_map<std::string, SongHistoryView> m_songRanges;

        bool m_coversAllData;

        std::vector<ListeningTimeRankingEntry> getListeningTimeRankingFromMap(
            const std::unordered_map<std::string, std::vector<std::string>>& map) const;
    };
    
} // namespace statistics
