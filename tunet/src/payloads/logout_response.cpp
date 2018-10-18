//
// Created by Hippolyte Barraud on 10/17/18.
//

#include "payloads/logout_response.hpp"

namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

tunet::payloads::logout_response::logout_response(boost::string_view json, boost::system::error_code &err)
        : json_object(json.substr(2, json.size() - 3), err) {
}
