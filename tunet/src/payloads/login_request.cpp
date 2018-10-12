//
// Created by Hippolyte Barraud on 10/10/18.
//

#include <payloads/login_request.hpp>
#include <crypto/base64.hpp>
#include <boost/algorithm/string/join.hpp>
#include <array>
#include <crypto/crypto_utils.hpp>
#include <crypto/charset.hpp>
#include <crypto/hmac.hpp>
#include <crypto/md5.hpp>
#include <crypto/sha1.hpp>

tunet::payloads::login_request::login_request(boost::string_view username, boost::string_view password,
                                        boost::string_view, boost::string_view challenge) : username(username),
                                                                                            password(password), ip("") {
    std::array<std::string, 11> c{R"({"username":")", username.to_string(), R"(","password":")", password.to_string(),
                                  R"(","ip":")", this->ip, R"(","acid":")", _ac_id, R"(","enc_ver":")", "srun_bx1",
                                  R"("})"};
    auto payload = boost::algorithm::join(c, "");

    _info = "{SRBX1}" + base64_encode(utf8_to_latin9(xEncode(payload, challenge)),
                                      "LVoJPiCN2R8G90yg+hmFHuacZ1OWMnrsSTXkYpUq/3dlbfKwv6xztjI7DeBE45QA");

    auto hmd5 = hmac<MD5>("pwd", challenge);
    this->password = "{MD5}" + hmd5;
    auto chalss = challenge.to_string();

    std::array<std::string, 14> hashcontent{chalss, this->username, chalss, hmd5, chalss, _ac_id, chalss, this->ip,
                                            chalss, _n, chalss, _type, chalss, _info};
    _chksum = SHA1()(boost::algorithm::join(hashcontent, ""));
}

std::string tunet::payloads::login_request::to_form_urlencoded() const {
    auto urlencoded = boost::algorithm::join<std::initializer_list<std::string>>(
            {"callback=x", "&action=", urlencode(action), "&username=", urlencode(username), "&password=", urlencode(password),
             "&ac_id=", urlencode(_ac_id), "&type=", urlencode(_type), "&n=", urlencode(_n), "&ip=", urlencode(ip),
             "&info=", urlencode(_info), "&chksum=", urlencode(_chksum)}, "");
    return urlencoded;
}
