#pragma once

#include <iostream>
#include <string>
#include <ctime>

#include "log.hpp"
#include "hlt_in.hpp"
#include "hlt_out.hpp"

std::string xput_time() 
{
    // While compilers like G++4.8 report C++11 compatibility, they do not
    // support std::put_time, so we have to use strftime instead.
    auto time = std::time(nullptr);
    auto localtime = std::localtime(&time);
    char result[30];
    std::strftime(result, 30, "%Y%m%d-%H%M%S%z-", localtime);
    return std::string(result);
}

namespace hlt {
    struct Metadata {
        const PlayerId player_id;
        const int map_width;
        const int map_height;
        const Map initial_map;
    };

    /// Initialize our bot with the given name, getting back some metadata.
    static Metadata initialize(const std::string& bot_name) {
        std::cout.sync_with_stdio(false);

        std::stringstream iss1(in::get_string());
        int player_id;
        iss1 >> player_id;

        std::stringstream iss2(in::get_string());
        int map_width;
        int map_height;
        iss2 >> map_width >> map_height;

        std::stringstream log_filename;
        log_filename    << player_id 
                        << "_" << bot_name 
                        << "_" << xput_time() 
                        <<  ".log";
        Log::open(log_filename.str());

        std::stringstream bot_name_with_decoration;
        bot_name_with_decoration << bot_name << "_" << player_id;
        out::send_string(bot_name_with_decoration.str());

        // halite sends full map as part of initialization, we can discard it since
        // we'll get it as first map update anyway, but if you want, you can parse
        // it using hlt::in::get_map
        const Map map = hlt::in::get_map(map_width, map_height);

        return { static_cast<PlayerId>(player_id), map_width, map_height, map };
    }
}
