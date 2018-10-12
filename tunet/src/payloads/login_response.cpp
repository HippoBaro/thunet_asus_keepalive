//
// Created by Hippolyte Barraud on 10/11/18.
//

#include <payloads/login_response.hpp>
#include <error_code.hpp>

tunet::payloads::login_response::login_response(boost::string_view json, boost::system::error_code &err) :
        json_payload(json, err) {
    if (err) {
        return;
    }

    auto ecode = this->operator[]<boost::string_view>("ecode");
    auto error = this->operator[]<boost::string_view>("error");
    if (ecode && !ecode->empty()) {
        err = make_error_code(static_cast<tunet_service_error>(std::atoi(ecode->data() + 1)));
    }
    else if (error && *error != "ok") {
        err = boost::system::errc::make_error_code(boost::system::errc::bad_message);
    }
}