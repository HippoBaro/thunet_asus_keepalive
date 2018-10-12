//
// Created by Hippolyte Barraud on 10/11/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_LOGIN_RESPONSE_HPP
#define THUNET_ASUS_KEEPALIVE_LOGIN_RESPONSE_HPP

#include <boost/utility/string_view.hpp>
#include <boost/system/error_code.hpp>
#include "payloads/json_payload.hpp"

namespace tunet::payloads {
    struct login_response : public json_payload {
    public:
        login_response() = delete;

        login_response(login_response const &) = delete;

        login_response(login_response &&) = default;

        explicit login_response(boost::string_view json, boost::system::error_code &err);
    };
}

#endif //THUNET_ASUS_KEEPALIVE_LOGIN_RESPONSE_HPP
