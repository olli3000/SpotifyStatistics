#include "statistics/data_frame_view.hpp"

namespace statistics
{
    // void printTime(std::chrono::system_clock::time_point time)
    // {
    //     std::time_t t = std::chrono::system_clock::to_time_t(time);

    //     std::cout << std::put_time(
    //         std::gmtime(&t),
    //         "%Y-%m-%d %H:%M:%S"
    //     );
    // }

    DataFrameView::DataFrameView(const DataFrame& data, const TimeRange& range) : m_data(data), m_range(range) {
        for (auto& [ID, history] : data.m_songData) {
            auto span = history.getSpanFromTimeRange(range);
            if (span.rangeHistory.empty()) continue;
            
            m_songRanges.emplace(ID, history.getSpanFromTimeRange(range));
            // if (ID == "61ZM92T2zaXIVsqncThQzC") {
                
            // }
        }

        if (range.begin <= data.m_historyBegin 
            && range.end >= data.m_historyEnd) {
            
            m_coversAllData = true;
        }
    }

    int DataFrameView::getNumberOfSongs() const {
        return m_songRanges.size();
    }

    int DataFrameView::getNumberOfArtists() const {
        if (m_coversAllData) {
            return m_data.m_artistToSongMapping.size();
        }

        int numOfArtists = 0;
        for (auto& [_, songs] : m_data.m_artistToSongMapping) {
            for (auto& song : songs) {
                if (m_songRanges.contains(song)) {
                    numOfArtists++;
                    break;
                }
            }
        }
        return numOfArtists;
    }

    long DataFrameView::getTotalStreamingTime() const {
        long totalTime = 0;
        for (auto& [_, history] : m_songRanges) {
            totalTime += history.total;
        }
        return totalTime;
    }

    std::vector<SongRankingEntry> DataFrameView::getSongsRanked() const {
        std::vector<SongRankingEntry> vec;

        for (auto& [ID, history] : m_songRanges) {
            vec.emplace_back(ID, 
                history.rangeHistory.front().master_metadata_track_name,
                history.rangeHistory.front().master_metadata_album_artist_name,
                history.total
            );
        }

        std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
            return a.listeningTime > b.listeningTime;
        });

        return vec;
    }

    std::vector<ArtistRankingEntry> DataFrameView::getArtistsRanked() const {
        std::vector<ArtistRankingEntry> vec;

        for (auto& [name, songs] : m_data.m_artistToSongMapping) {
            long time = 0;
            
            for (auto& song : songs) {
                if (m_songRanges.contains(song)) {
                    time += m_songRanges.at(song).total;
                }
            }

            vec.emplace_back(name, time);
        }

        std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
            return a.listeningTime > b.listeningTime;
        });

        return vec;
    }

} // namespace statistics
