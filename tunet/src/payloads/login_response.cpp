//
// Created by Hippolyte Barraud on 10/11/18.
//

#include "login_response.hpp"
#include <error_code.hpp>

tunet::payloads::login_response::login_response(boost::string_view) {

}

boost::optional<tunet::payloads::login_response>
tunet::payloads::login_response::make(boost::beast::http::response<boost::beast::http::string_body> &res,
                                      boost::system::error_code &err) {
    printf("%s\n", res.body().data());
    boost::string_view error_response("login_error");
    if (res.result() != boost::beast::http::status::ok ||
        std::equal(res.body().begin(), res.body().begin() + error_response.size(), error_response.begin())) {
        err = make_error_code(tunet_service_error::failed_challenge_retrieval);
        return {};
    }
    return tunet::payloads::login_response(res.body());
}
