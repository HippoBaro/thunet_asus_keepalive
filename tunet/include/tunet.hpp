//
// Created by Hippolyte Barraud on 10/11/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_TUNET_HPP
#define THUNET_ASUS_KEEPALIVE_TUNET_HPP

#include <boost/asio/io_context.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/optional.hpp>
#include "payloads/status_response.hpp"
#include "payloads/login_response.hpp"

namespace tunet {
    boost::optional<tunet::payloads::login_response>
    login(boost::asio::io_context &ioc, std::vector<std::pair<boost::string_view, boost::string_view>> credentials,
          boost::system::error_code &ec) noexcept;

    boost::optional<tunet::payloads::status_response>
    status(boost::asio::io_context &ioc, boost::system::error_code &ec) noexcept;
}

#endif //THUNET_ASUS_KEEPALIVE_TUNET_HPP
