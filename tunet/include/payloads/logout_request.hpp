//
// Created by Hippolyte Barraud on 10/17/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_LOGOUT_REQUEST_HPP
#define THUNET_ASUS_KEEPALIVE_LOGOUT_REQUEST_HPP

#include <boost/noncopyable.hpp>
#include <boost/utility/string_view.hpp>

namespace tunet::payloads {
    struct logout_request : boost::noncopyable {
        static constexpr auto action = "logout";
        std::string username;
        std::string ip;

        logout_request() = delete;

        logout_request(boost::string_view username, boost::string_view challenge,
                       boost::string_view ip);

        std::string to_form_urlencoded() const;

    private:
        static constexpr auto _ac_id = "1";
        static constexpr auto _type = "1";
        static constexpr auto _n = "200";
        std::string _info = "";
        std::string _chksum = "";
    };
}

#endif //THUNET_ASUS_KEEPALIVE_LOGOUT_REQUEST_HPP
