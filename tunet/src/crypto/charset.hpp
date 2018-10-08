//
// Created by Hippolyte Barraud on 10/10/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_CHARSET_HPP
#define THUNET_ASUS_KEEPALIVE_CHARSET_HPP

#include <boost/utility/string_view.hpp>

size_t utf8_to_latin9(char * output, const char * input, size_t length);
std::string utf8_to_latin9(boost::string_view utf8);
std::string urlencode(boost::string_view s);

#endif //THUNET_ASUS_KEEPALIVE_CHARSET_HPP
