//
// Created by Hippolyte Barraud on 10/10/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_LOGIN_PAYLOAD_HPP
#define THUNET_ASUS_KEEPALIVE_LOGIN_PAYLOAD_HPP

#include <boost/noncopyable.hpp>
#include <boost/utility/string_view.hpp>

namespace tunet::payloads {
    struct login_request : boost::noncopyable {
        static constexpr auto action = "login";
        std::string username;
        std::string password;
        std::string ip;

        login_request() = delete;
        login_request(boost::string_view username, boost::string_view password, boost::string_view ip, boost::string_view challenge);

        std::string to_form_urlencoded() const;

    private:
        static constexpr auto _ac_id = "1";
        static constexpr auto _type = "1";
        static constexpr auto _n = "200";
        std::string _info = "";
        std::string _chksum = "";
    };
}



#endif //THUNET_ASUS_KEEPALIVE_LOGIN_PAYLOAD_HPP
