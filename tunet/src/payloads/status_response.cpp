//
// Created by Hippolyte Barraud on 10/12/18.
//

#include <string>
#include <boost/algorithm/string.hpp>
#include <payloads/status_response.hpp>

namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

tunet::payloads::status_response::status_response(boost::string_view content, boost::system::error_code &) {
    std::vector<std::string> elements;
    boost::algorithm::split(elements, content, boost::is_any_of(","));
    if (elements.size() < 13) {
        return;
    }

    username = elements[0];
    login_date = std::stoll(elements[1]);
    query_date = std::stoll(elements[2]);
    ingress = std::stoull(elements[3]);
    egress = std::stoull(elements[4]);
    //5 unknown
    traffic = std::stoull(elements[6]);
    connected_time = std::stoull(elements[7]);
    ipv4 = elements[8];
    //9 unknown
    //10 unknown
    balance = std::stod(elements[11]);
    //10 unknown
    connected = true;
}