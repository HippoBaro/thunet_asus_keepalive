//
// Created by Hippolyte Barraud on 10/11/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_CHALLENGE_REQUEST_HPP
#define THUNET_ASUS_KEEPALIVE_CHALLENGE_REQUEST_HPP

#include <boost/utility/string_view.hpp>

namespace tunet::payloads  {
    struct challenge_request {
        boost::string_view username;
        boost::string_view ip;

        challenge_request() = delete;
        challenge_request(boost::string_view username, boost::string_view ip);

        std::string to_form_urlencoded() const;
    };
}


#endif //THUNET_ASUS_KEEPALIVE_CHALLENGE_REQUEST_HPP
