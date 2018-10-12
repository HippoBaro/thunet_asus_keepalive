//
// Created by Hippolyte Barraud on 10/10/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_CHALLENGE_HPP
#define THUNET_ASUS_KEEPALIVE_CHALLENGE_HPP

#include <json/gason.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include "json_payload.hpp"

namespace tunet::payloads {

    struct challenge_response : public json_payload {
        challenge_response() = delete;

        challenge_response(challenge_response const &) = delete;

        challenge_response(challenge_response &&) = default;

        explicit challenge_response(boost::string_view json, boost::system::error_code &err);
    };
}


#endif //THUNET_ASUS_KEEPALIVE_CHALLENGE_HPP


//maxiao17,   1539297477,      1539312425,      175117807,                  13178402,                   0,  14383359025,          915834,                   59.66.229.24,   0,  ,   0.000000,  0
//'Username', 'Time of login', 'Time of query', 'Session traffic incoming', 'Session traffic outgoing', "", 'Cumulative traffic', 'Cumulative online time', 'IPv4 Address', "", "", 'Balance', ""