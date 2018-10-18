//
// Created by Hippolyte Barraud on 10/17/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_LOGOUT_RESPONSE_HPP
#define THUNET_ASUS_KEEPALIVE_LOGOUT_RESPONSE_HPP

#include <json_object.hpp>

namespace tunet::payloads {
    struct logout_response : public json_object {
    public:
        logout_response() = delete;

        logout_response(logout_response &&) = default;

        explicit logout_response(boost::string_view json, boost::system::error_code &err);
    };
}


#endif //THUNET_ASUS_KEEPALIVE_LOGOUT_RESPONSE_HPP
