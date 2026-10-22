#pragma once

#include <string_view>
#include <chrono>

namespace statistics
{
    struct TimeRange {
        std::chrono::sys_seconds begin;
        std::chrono::sys_seconds end;

        bool operator==(const TimeRange& other) const = default;
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

template<>
struct std::hash<statistics::TimeRange> {
    std::size_t operator()(const statistics::TimeRange& range) const noexcept {
        auto h1 = std::hash<std::chrono::seconds::rep>{}(range.begin.time_since_epoch().count());
        auto h2 = std::hash<std::chrono::seconds::rep>{}(range.end.time_since_epoch().count());

        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};