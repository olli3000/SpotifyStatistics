#pragma once

#include <vector>
#include <unordered_map>

#include "nlohmann/json.hpp"
#include "json_data_entry.hpp"
#include "song_history.hpp"
#include "util.hpp"

using json = nlohmann::json;

namespace statistics
{
    class DataFrame {
    public:
        DataFrame(char* pathToDir);

        void print();

        TimeRange getFullTimeRange() const;
        
    private:
        friend class DataFrameView;
    
        std::unordered_map<std::string, SongHistory> m_songData;
        std::unordered_map<std::string, std::vector<std::string>> m_artistToSongMapping;
        std::unordered_map<std::string, std::vector<std::string>> m_albumToSongMapping;

        std::chrono::sys_seconds m_historyBegin;
        std::chrono::sys_seconds m_historyEnd;
        bool m_isHistoryBeginSet;

        void addStreamingHistory(json& data);
        void linkArtistsAndAlbumsToSongs();
    };
} // namespace statistics
