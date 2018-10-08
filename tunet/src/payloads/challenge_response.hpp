//
// Created by Hippolyte Barraud on 10/10/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_CHALLENGE_HPP
#define THUNET_ASUS_KEEPALIVE_CHALLENGE_HPP

#include <json/gason.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>

namespace tunet::payloads {

    struct challenge_response {
    private:
        JsonNode *_node;
    public:
        std::string uid;
        std::string client_id;
        double ecode;
        std::string error;
        std::string error_message;
        std::string expire;
        std::string online_ip;
        std::string res;
        std::string srun_ver;
        double st;

        challenge_response() = delete;

        challenge_response(challenge_response const &) = delete;

        challenge_response(challenge_response &&) = default;

        explicit challenge_response(JsonValue &json);

        static boost::optional<challenge_response>
        make(boost::beast::http::response<boost::beast::http::string_body> &, boost::system::error_code &err);
    };
}


#endif //THUNET_ASUS_KEEPALIVE_CHALLENGE_HPP
