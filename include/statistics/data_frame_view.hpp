#pragma once

#include "statistics/data_frame.hpp"

namespace statistics
{
    class DataFrameView {
    public:
        DataFrameView(const DataFrame& data, const TimeRange& range);

        int getNumberOfSongs() const;
        int getNumberOfArtists() const;
        long getTotalStreamingTime() const;

        std::vector<SongRankingEntry> getSongsRanked() const;
        std::vector<ArtistRankingEntry> getArtistsRanked() const;

    private:
        const DataFrame& m_data;
        const TimeRange m_range;

        std::unordered_map<std::string, SongHistoryView> m_songRanges;

        bool m_coversAllData;
    };
    
} // namespace statistics
