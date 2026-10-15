#pragma once

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace statistics
{
    struct JsonDataEntry {
        std::chrono::sys_seconds ts;
        std::string platform;
        int ms_played;
        // std::string conn_country;
        // std::string ip_addr;
        std::string master_metadata_track_name;
        std::string master_metadata_album_artist_name;
        std::string master_metadata_album_album_name;
        std::string spotify_track_uri;
        // std::string episode_name;
        // std::string episode_show_name;
        // std::string spotify_episode_uri;
        // std::string audiobook_title;
        // std::string audiobook_uri;
        // std::string audiobook_chapter_uri;
        // std::string audiobook_chapter_title;
        std::string reason_start;
        std::string reason_end;
        bool shuffle;
        bool skipped;
        bool offline;
        int offline_timestamp;
        bool incognito_mode;

        std::string getID() {
            std::string id = spotify_track_uri.empty() ? "" : spotify_track_uri.substr(14);
            // id += spotify_episode_uri.empty() ? "" : spotify_episode_uri.substr(16);
            return id;
        }

        std::string to_string() {
            return master_metadata_track_name;
        }
    };

    inline void from_json(const json& j, JsonDataEntry& d) {
        if (!j.at("ts").is_null()) {
            std::string temp_ts;
            j.at("ts").get_to(temp_ts);

            int year;
            unsigned month, day, hour, minute, second;
            std::sscanf(temp_ts.c_str(), "%d-%u-%uT%u:%u:%uZ", &year, &month, &day, &hour, &minute, &second);
            
            auto date = std::chrono::year_month_day{
                std::chrono::year{year}, 
                std::chrono::month{month}, 
                std::chrono::day{day}
            };

            d.ts = std::chrono::sys_days{date} 
                + std::chrono::hours{hour} 
                + std::chrono::minutes{minute} 
                + std::chrono::seconds{second};
        }
        if (!j.at("platform").is_null()) {
            j.at("platform").get_to(d.platform);
        }

        j.at("ms_played").get_to(d.ms_played);
        
        // if (!j.at("conn_country").is_null()) {
        //     j.at("conn_country").get_to(d.conn_country);
        // }
        // if (!j.at("ip_addr").is_null()) {
        //     j.at("ip_addr").get_to(d.ip_addr);
        // }
        if (!j.at("master_metadata_track_name").is_null()) {
            j.at("master_metadata_track_name").get_to(d.master_metadata_track_name);
        }
        if (!j.at("master_metadata_album_artist_name").is_null()) {
            j.at("master_metadata_album_artist_name").get_to(d.master_metadata_album_artist_name);
        }
        if (!j.at("master_metadata_album_album_name").is_null()) {
            j.at("master_metadata_album_album_name").get_to(d.master_metadata_album_album_name);
        }
        if (!j.at("spotify_track_uri").is_null()) {
            j.at("spotify_track_uri").get_to(d.spotify_track_uri);
        }
        // if (!j.at("episode_name").is_null()) {
        //     j.at("episode_name").get_to(d.episode_name);
        // }
        // if (!j.at("episode_show_name").is_null()) {
        //     j.at("episode_show_name").get_to(d.episode_show_name);
        // }
        // if (!j.at("spotify_episode_uri").is_null()) {
        //     j.at("spotify_episode_uri").get_to(d.spotify_episode_uri);
        // }
        // if (!j.at("audiobook_title").is_null()) {
        //     j.at("audiobook_title").get_to(d.audiobook_title);
        // }
        // if (!j.at("audiobook_uri").is_null()) {
        //     j.at("audiobook_uri").get_to(d.audiobook_uri);
        // }
        // if (!j.at("audiobook_chapter_uri").is_null()) {
        //     j.at("audiobook_chapter_uri").get_to(d.audiobook_chapter_uri);
        // }
        // if (!j.at("audiobook_chapter_title").is_null()) {
        //     j.at("audiobook_chapter_title").get_to(d.audiobook_chapter_title);
        // }
        if (!j.at("reason_start").is_null()) {
            j.at("reason_start").get_to(d.reason_start);
        }
        if (!j.at("reason_end").is_null()) {
            j.at("reason_end").get_to(d.reason_end);
        }

        j.at("shuffle").get_to(d.shuffle);
        j.at("skipped").get_to(d.skipped);
        j.at("offline").get_to(d.offline);
        
        if (!j.at("offline_timestamp").is_null()) {
            j.at("offline_timestamp").get_to(d.offline_timestamp);
        }
        
        j.at("incognito_mode").get_to(d.incognito_mode);
    }
} // namespace statistics
