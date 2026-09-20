#include "statistics/data_frame.hpp"

#include <fstream>
#include <iostream>
#include <tuple>

namespace statistics
{
    // constructor

    DataFrame::DataFrame(char* pathToDir) {
        auto dirIterator = std::filesystem::directory_iterator(pathToDir);

        for (auto& entry : dirIterator) {
            if (entry.is_regular_file() && 
                entry.path().extension() != ".pdf" && 
                entry.path().filename().string().find("Audio") != std::string::npos) {
                
                std::ifstream file(entry.path());
                json data = json::parse(file);
                addStreamingHistory(data);
            }
        }

        linkArtistsAndAlbumsToSongs();
    }

    // public

    TimeRange DataFrame::getFullTimeRange() const {
        return {m_historyBegin, m_historyEnd};
    }

    // private

    void DataFrame::addStreamingHistory(json& data) {
        std::vector<statistics::JsonDataEntry> list = data.get<std::vector<statistics::JsonDataEntry>>();

        if (!m_isHistoryBeginSet) {
            m_historyBegin = list.front().ts;
            m_isHistoryBeginSet = true;
        }

        for (auto& entry : list) {
            std::string id = entry.getID();
            {
                auto [it, inserted] = m_songData.try_emplace(id, std::move(entry));
                if (!inserted) {
                    it->second.addInstance(std::move(entry));
                }
            }
        }

        m_historyEnd = list.back().ts;
    }

    void DataFrame::linkArtistsAndAlbumsToSongs() {
        for (auto& [id, history] : m_songData) {
            {
                std::string artistName{history.getArtist()};
                auto [it, inserted] = m_artistToSongMapping.try_emplace(artistName, std::vector<std::string>{id});
                if (!inserted) {
                    it->second.push_back(id);
                }
            }

            {
                std::string albumName{history.getAlbum()};
                auto [it, inserted] = m_albumToSongMapping.try_emplace(albumName, std::vector<std::string>{id});
                if (!inserted) {
                    it->second.push_back(id);
                }
            }
        }
    }

    // test

    bool cmpArtistSongs(std::pair<std::string, std::vector<std::string>>& a, std::pair<std::string, std::vector<std::string>>& b) {
        return a.second.size() > b.second.size();
    }

    void printSongsPerArtist(std::unordered_map<std::string, std::vector<std::string>>& artistToSongMapping) {
        std::vector<std::pair<std::string, std::vector<std::string>>> vec;
        for (auto& pair : artistToSongMapping) {
            vec.push_back(pair);
        }

        std::sort(vec.begin(), vec.end(), cmpArtistSongs);

        for (auto& [artist, songs] : vec) {
            std::cout << artist << ": " << songs.size() << std::endl;
        }
    }

    bool cmpSongHistory(std::pair<std::string, SongHistory>& a, std::pair<std::string, SongHistory>& b) {
        // return a.second.size() > b.second.size();
        return a.second.total() > b.second.total();
    }

    void printSongHistory(std::unordered_map<std::string, SongHistory>& songData) {
        std::vector<std::pair<std::string, SongHistory>> vec;
        for (auto& pair : songData) {
            vec.push_back(pair);
        }

        std::sort(vec.begin(), vec.end(), cmpSongHistory);

        for (auto& [id, history] : vec) {
            std::cout << id << " " << history.getArtist() << " - " << history.getTitle() << " - " << (history.total() / 3'600'000.0) << std::endl;
        }
    }

    // void printTimePerArtist(std::unordered_map<std::string, SongHistory>& songData,
    //                         std::unordered_map<std::string, std::vector<std::string>>& artistToSongMapping) {
    //     std::vector<std::pair<std::string, long>> vec;
    //     for (auto& pair : artistToSongMapping) {
    //         long time = 0;
    //         for (auto& song : pair.second) {
    //             time += songData.at(song).total();
    //         }
    //         vec.emplace_back(pair.first, time);
    //     }

    //     std::sort(vec.begin(), vec.end(), cmpArtistListeningTime);

    //     for (auto& [name, time] : vec) {
    //         std::cout << name << ": " << (time / 3'600'000.0) << std::endl;
    //     }
    // }

    void printRatioSkipped(std::unordered_map<std::string, SongHistory>& songData) {
        std::vector<std::pair<std::string, double>> vec;
        for (auto& pair : songData) {
            vec.emplace_back((pair.first + " ").append(pair.second.getTitle()), pair.second.calcRatioSkipped());
        }

        std::sort(vec.begin(), vec.end(), [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
            return a.second < b.second;
        });

        for (auto& [name, skipped] : vec) {
            std::cout << name << ": " << skipped << "\% skipped" << std::endl;
        }
    }

    void DataFrame::print() {
        std::cout << "Data:" << std::endl;
        // for (auto& [_, history] : _songData) {
        //     // if (instances.getTitle() == "Lost") {
        //     //     std::cout << "Found\n";
        //     // }
        //     std::cout << history.toString() << std::endl;
        // }
        
        // printSongsPerArtist(_artistToSongMapping);
        // printSongHistory(_songData);
        // printTimePerArtist(_songData, _artistToSongMapping);
        // printRatioSkipped(_songData);
    }

} // namespace statistics
