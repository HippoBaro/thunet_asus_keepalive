//
// Created by Hippolyte Barraud on 10/10/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_LOGIN_PAYLOAD_HPP
#define THUNET_ASUS_KEEPALIVE_LOGIN_PAYLOAD_HPP

#include <boost/noncopyable.hpp>
#include <boost/utility/string_view.hpp>

namespace tunet::payloads {
    struct login_request : boost::noncopyable {
        std::string action = "login";
        std::string username;
        std::string password;
        std::string ip;

        login_request() = delete;
        login_request(login_request &&) = default;
        login_request(boost::string_view username, boost::string_view password, boost::string_view ip, boost::string_view challenge);

        std::string to_form_urlencoded() const;

    private:
        std::string _ac_id = "1";
        std::string _type = "1";
        std::string _n = "200";
        std::string _info = "";
        std::string _chksum = "";
    };
}



#endif //THUNET_ASUS_KEEPALIVE_LOGIN_PAYLOAD_HPP
