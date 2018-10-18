//
// Created by Hippolyte Barraud on 10/14/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_LOGGER_HPP
#define THUNET_ASUS_KEEPALIVE_LOGGER_HPP

#include <ctime>
#include <boost/circular_buffer.hpp>
#include <boost/utility/string_view.hpp>

enum class log_level : int {
    debug = 0,
    info = 1,
    warning = 2,
    error = 3,
    critical = 4
};

struct logger {
    boost::circular_buffer<std::tuple<log_level, std::time_t, std::string>> buf = boost::circular_buffer<std::tuple<log_level, std::time_t, std::string>>(100);
    void operator()(boost::string_view, log_level = log_level::info);

    std::string format(std::tuple<log_level, std::time_t, std::string> const& log);
};

extern std::unique_ptr<logger> logger_;


#endif //THUNET_ASUS_KEEPALIVE_LOGGER_HPP
