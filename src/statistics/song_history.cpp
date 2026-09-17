#include "statistics/song_history.hpp"

#include <iostream>
#include <string>

namespace statistics
{
    SongHistory::SongHistory(JsonDataEntry&& firstInstance) : _id(firstInstance.getID()) {
        _instances.push_back(firstInstance);
        updateMinMaxTotalAvg(firstInstance);
    }

    void SongHistory::addInstance(JsonDataEntry&& instance) {
        _instances.push_back(instance);
        updateMinMaxTotalAvg(instance);
    }

    std::span<const JsonDataEntry> SongHistory::getSpanFromTimeRange(const TimeRange& range) const
    {
        auto begin = std::lower_bound(_instances.begin(), _instances.end(), range.begin, 
        [](const JsonDataEntry& entry, const auto& timestamp) {
            return entry.ts < timestamp;
        });

        auto end = std::upper_bound(_instances.begin(), _instances.end(), range.end, 
        [](const auto& timestamp, const JsonDataEntry& entry) {
            return timestamp < entry.ts;
        });

        return {begin, end};
    }

    void SongHistory::updateMinMaxTotalAvg(JsonDataEntry& instance) {
        if (_min == -1 || instance.ms_played < _instances[_min].ms_played) _min = size() - 1;
        if (_max == -1 || instance.ms_played > _instances[_max].ms_played) _max = size() - 1;
        _total += instance.ms_played;
        _avg = _total / size();
    }

    std::string_view SongHistory::getID() const {
        return _id;
    }

    std::string_view SongHistory::getTitle() const {
        return _instances.front().master_metadata_track_name;
    }

    std::string_view SongHistory::getArtist() const {
        return _instances.front().master_metadata_album_artist_name;
    }

    std::string_view SongHistory::getAlbum() const {
        return _instances.front().master_metadata_album_album_name;
    }

    size_t SongHistory::size() const {
        return _instances.size();
    }

    int SongHistory::total() const {
        return _total;
    }

    double SongHistory::calcRatioSkipped() {
        int countSkipped = 0;

        for (auto& song : _instances) {
            if (song.reason_end == "fwdbtn" || song.reason_end == "backbtn" || song.reason_end == "endplay") {
                countSkipped++;
            }
        }

        return (countSkipped * 100.0) / _instances.size();
    }

    std::string SongHistory::toString()
    {
        // return _instances.at(0).getID();
        // return (_id + " ").append(_title);
        // return _title;
        // return std::to_string(_instances.size());
        return (_id + " - ").append(getArtist()).append(" - ").append(getTitle()).append(" - ").append(getAlbum()).append(" - ").append(std::to_string(_total));
    }
    
} // namespace statistics
