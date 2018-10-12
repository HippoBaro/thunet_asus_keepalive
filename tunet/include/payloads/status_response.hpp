//
// Created by Hippolyte Barraud on 10/12/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_STATUS_RESPONSE_HPP
#define THUNET_ASUS_KEEPALIVE_STATUS_RESPONSE_HPP

#include <chrono>
#include <boost/utility/string_view.hpp>
#include <boost/system/error_code.hpp>

namespace tunet::payloads {

    struct status_response {
        bool connected = false;
        std::string username;
        std::time_t login_date;
        std::time_t query_date;
        std::size_t ingress;
        std::size_t egress;
        int unknown;
        std::size_t traffic;
        std::chrono::seconds connected_time;
        std::string ipv4;
        int unknown2;
        int unknown3;
        double balance;
        int unknown4;

        status_response() = delete;

        status_response(status_response const &) = delete;

        status_response(status_response &&) = default;

        explicit status_response(boost::string_view content, boost::system::error_code &err);
    };
}


#endif //THUNET_ASUS_KEEPALIVE_STATUS_RESPONSE_HPP
