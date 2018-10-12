//
// Created by Hippolyte Barraud on 10/10/18.
//

#include <payloads/challenge_response.hpp>
#include "challenge_response.hpp"
#include <json/gason.hpp>
#include <error_code.hpp>

tunet::payloads::challenge_response::challenge_response(boost::string_view json, boost::system::error_code &err) :
    json_payload(json, err) {
    if (err) {
        return;
    }
    if (!this->operator[]<boost::string_view>("challenge") || this->operator[]<boost::string_view>("challenge")->empty()) {
        err = make_error_code(tunet_service_error::failed_challenge_retrieval);
    }
}
