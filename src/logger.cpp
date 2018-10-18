//
// Created by Hippolyte Barraud on 10/14/18.
//

#include "logger.hpp"

static boost::string_view level_to_string(log_level lv) {
    switch (lv) {
        case log_level::debug: return       "   DEBUG";
        case log_level::info: return        "    INFO";
        case log_level::warning: return     " WARNING";
        case log_level::error: return       "   ERROR";
        case log_level::critical: return    "CRITICAL";
        default: return                     " UNKNOWN";
    }
}

void logger::operator()(boost::string_view log, log_level level) {
    _buf.push_back(std::make_pair(std::time(nullptr), log.to_string()));

    if (_buf.full() || level >= log_level::error) {
        //store
    }

    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%F %T", std::localtime(&_buf.back().first))) {
        printf("%s [%s]: %s\n", mbstr, level_to_string(level).data(), log.data());
    }
}
