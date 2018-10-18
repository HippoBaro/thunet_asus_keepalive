//
// Created by Hippolyte Barraud on 10/17/18.
//

#include <payloads/logout_request.hpp>
#include <boost/algorithm/string/join.hpp>
#include <crypto/charset.hpp>
#include <crypto/crypto_utils.hpp>
#include <crypto/base64.hpp>
#include <crypto/sha1.hpp>

namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

tunet::payloads::logout_request::logout_request(boost::string_view username, boost::string_view challenge,
                                                boost::string_view ip) : username(
        username), ip(ip) {
    auto payload = boost::algorithm::join<std::initializer_list<std::string>>(
            {R"({"username":")", this->username, R"(","ip":"")", R"(,"acid":")", _ac_id, R"(","enc_ver":")", "srun_bx1",
             R"("})"}, "");

    _info = "{SRBX1}" + base64_encode(utf8_to_latin9(xEncode(payload, challenge)),
                                      "LVoJPiCN2R8G90yg+hmFHuacZ1OWMnrsSTXkYpUq/3dlbfKwv6xztjI7DeBE45QA");

    auto chalss = challenge.to_string();
    _chksum = SHA1()(boost::algorithm::join<std::initializer_list<std::string>>(
            {chalss, this->username, chalss, _ac_id, chalss, this->ip, chalss, _n, chalss, _type, chalss,_info}, ""));
}

std::string tunet::payloads::logout_request::to_form_urlencoded() const {
    auto ts = std::chrono::duration_cast< std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    auto urlencoded = boost::algorithm::join<std::initializer_list<std::string>>(
            {"callback=x", "&action=", urlencode(action), "&username=", urlencode(username),
             "&ac_id=", urlencode(_ac_id), "&ip=", urlencode(ip), "&double_stack=1",
             "&info=", urlencode(_info), "&chksum=", urlencode(_chksum), "&n=", urlencode(_n), "&type=", urlencode(_type), "&_=", std::to_string(ts)}, "");
    return urlencoded;
}
