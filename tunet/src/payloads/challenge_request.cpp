//
// Created by Hippolyte Barraud on 10/11/18.
//

#include <boost/algorithm/string/join.hpp>
#include <crypto/charset.hpp>
#include "payloads/challenge_request.hpp"

namespace tunet::payloads {
    challenge_request::challenge_request(boost::string_view username, boost::string_view ip) :
            username(username), ip(ip) {}

    std::string challenge_request::to_form_urlencoded() const {
        auto urlencoded = boost::algorithm::join<std::initializer_list<std::string>>(
                {"callback=x", "&username=", urlencode(username), "&ip=", urlencode(ip)}, "");
        return urlencoded;
    }
}
