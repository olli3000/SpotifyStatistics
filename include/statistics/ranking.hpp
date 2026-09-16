#pragma once

#include <string_view>

namespace statistics
{
    struct SongRankingEntry {
        std::string_view id;
        std::string_view title;
        std::string_view artist;
        long listeningTime;
    };

    struct ArtistRankingEntry {
        std::string_view name;
        long listeningTime;
    };
    
} // namespace statistics
