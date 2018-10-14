//
// Created by Hippolyte Barraud on 10/14/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_LOGGER_HPP
#define THUNET_ASUS_KEEPALIVE_LOGGER_HPP

#include <ctime>
#include <string>
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
private:
    boost::circular_buffer<std::pair<std::time_t, std::string>> _buf = boost::circular_buffer<std::pair<std::time_t, std::string>>(100);

public:

    void operator()(boost::string_view, log_level = log_level::info);
};

static logger logger_ = logger();


#endif //THUNET_ASUS_KEEPALIVE_LOGGER_HPP
