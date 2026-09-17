#pragma once

#include <vector>
#include <map>

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
        
        int getNumberOfSongs() const;
        int getNumberOfArtists() const;
        long getTotalStreamingTime() const;

        std::vector<ArtistRankingEntry> getArtistsRanked() const;
        std::vector<SongRankingEntry> getSongsRanked() const;

    private:
        friend class DataFrameView;
    
        std::unordered_map<std::string, SongHistory> _songData;
        std::unordered_map<std::string, std::vector<std::string>> _artistToSongMapping;
        std::unordered_map<std::string, std::vector<std::string>> _albumToSongMapping;

        void addStreamingHistory(json& data);
        void linkArtistsAndAlbumsToSongs();
    };
} // namespace statistics
