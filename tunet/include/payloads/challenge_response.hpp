//
// Created by Hippolyte Barraud on 10/10/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_CHALLENGE_HPP
#define THUNET_ASUS_KEEPALIVE_CHALLENGE_HPP

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
