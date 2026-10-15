#pragma once

#include <string_view>
#include <chrono>

namespace statistics
{
    struct TimeRange {
        std::chrono::sys_seconds begin;
        std::chrono::sys_seconds end;
    };

    struct SongRankingEntry {
        std::string_view id;
        std::string_view title;
        std::string_view artist;
        long listeningTime;
    };

    struct ListeningTimeRankingEntry {
        std::string_view name;
        long listeningTime;
    };
    
} // namespace statistics
