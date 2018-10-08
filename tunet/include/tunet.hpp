//
// Created by Hippolyte Barraud on 10/11/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_TUNET_HPP
#define THUNET_ASUS_KEEPALIVE_TUNET_HPP

#include <boost/asio/io_context.hpp>
#include <boost/utility/string_view.hpp>

namespace tunet {
    void keepalive(boost::asio::io_context & ioc, std::vector<std::pair<boost::string_view, boost::string_view>> credentials, boost::system::error_code &ec) noexcept;
}

#endif //THUNET_ASUS_KEEPALIVE_TUNET_HPP
