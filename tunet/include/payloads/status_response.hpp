//
// Created by Hippolyte Barraud on 10/12/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_STATUS_RESPONSE_HPP
#define THUNET_ASUS_KEEPALIVE_STATUS_RESPONSE_HPP

#include <boost/utility/string_view.hpp>
#include <boost/system/error_code.hpp>

//maxiao17,   1539297477,      1539312425,      175117807,                  13178402,                   0,  14383359025,          915834,                   59.66.229.24,   0,  ,   0.000000,  0
//'Username', 'Time of login', 'Time of query', 'Session traffic incoming', 'Session traffic outgoing', "", 'Cumulative traffic', 'Cumulative online time', 'IPv4 Address', "", "", 'Balance', ""

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
