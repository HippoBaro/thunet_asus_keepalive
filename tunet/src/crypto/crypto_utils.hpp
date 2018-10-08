//
// Created by Hippolyte Barraud on 10/10/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_CRYPTO_UTILS_HPP
#define THUNET_ASUS_KEEPALIVE_CRYPTO_UTILS_HPP

#include <boost/utility/string_view.hpp>

std::string xEncode(boost::string_view str, boost::string_view key);

#endif //THUNET_ASUS_KEEPALIVE_CRYPTO_UTILS_HPP
