//
// Created by Hippolyte Barraud on 10/10/18.
//

#include <payloads/challenge_response.hpp>
#include "challenge_response.hpp"
#include <json/gason.hpp>
#include <error_code.hpp>

inline JsonNode * get_next(JsonNode **origin) {
    auto ret = *origin;
    *origin = (*origin)->next;
    return ret;
}

tunet::payloads::challenge_response::challenge_response(JsonValue &json) :
    _node(json.toNode()),
    uid(get_next(&_node)->value.toString()),
    client_id(get_next(&_node)->value.toString()),
    ecode(get_next(&_node)->value.toNumber()),
    error(get_next(&_node)->value.toString()),
    error_message(get_next(&_node)->value.toString()),
    expire(get_next(&_node)->value.toString()),
    online_ip(get_next(&_node)->value.toString()),
    res(get_next(&_node)->value.toString()),
    srun_ver(get_next(&_node)->value.toString()),
    st(get_next(&_node)->value.toNumber()) { }

boost::optional<tunet::payloads::challenge_response>
tunet::payloads::challenge_response::make(boost::beast::http::response<boost::beast::http::string_body> & res,
                                         boost::system::error_code &err) {
    if (res.result() != boost::beast::http::status::ok) {
        err = make_error_code(tunet_service_error::failed_challenge_retrieval);
        return {};
    }

    JsonValue value;
    JsonAllocator allocator;
    auto begin = const_cast<char *>(res.body().data()) + 2; //work-around GCC6.2 bug
    auto end = &(*(res.body().end() - 1));
    int status = jsonParse(begin, &end, &value, allocator);
    if (status != JSON_OK) {
        err = make_error_code(boost::system::errc::bad_message);
        return {};
    }
    return tunet::payloads::challenge_response(value);
}