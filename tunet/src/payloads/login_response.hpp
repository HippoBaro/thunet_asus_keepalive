//
// Created by Hippolyte Barraud on 10/11/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_LOGIN_RESPONSE_HPP
#define THUNET_ASUS_KEEPALIVE_LOGIN_RESPONSE_HPP

#include <boost/optional.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/beast/http/string_body.hpp>

namespace tunet::payloads {
    struct login_response {
        login_response() = delete;

        login_response(login_response const &) = delete;

        login_response(login_response &&) = default;

        explicit login_response(boost::string_view);

        static boost::optional<login_response>
        make(boost::beast::http::response<boost::beast::http::string_body> &, boost::system::error_code &err);
    };
}

#endif //THUNET_ASUS_KEEPALIVE_LOGIN_RESPONSE_HPP
