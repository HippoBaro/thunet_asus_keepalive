//
// Created by Hippolyte Barraud on 10/14/18.
//

#include "logger.hpp"

std::unique_ptr<logger> logger_ = nullptr;

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
    buf.push_back(std::make_tuple(level, std::time(nullptr), log.to_string()));

    if (buf.full() || level >= log_level::error) {
        //store
    }

    printf("%s\n", format(buf.back()).data());
}

std::string logger::format(std::tuple<log_level, std::time_t, std::string> const &log) {
    char mbstr[100];
    if (auto i = std::strftime(mbstr, sizeof(mbstr), "%F %T", std::localtime(&std::get<1>(log)))) {
        return std::string(mbstr, i) + " [" + level_to_string(std::get<0>(log)).to_string() + "]: " + std::get<2>(log);
    }
    return "";
}
