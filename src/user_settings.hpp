//
// Created by Hippolyte Barraud on 10/14/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_USER_SETTINGS_HPP
#define THUNET_ASUS_KEEPALIVE_USER_SETTINGS_HPP


#include <json_object.hpp>

struct user_settings : public json_object {
    using account_container = std::vector<std::pair<boost::string_view, boost::string_view>>;

    std::vector<std::pair<boost::string_view, boost::string_view>> accounts;

    user_settings();

    user_settings(boost::string_view source, boost::system::error_code &err);

    static std::unique_ptr<user_settings> make_from_fs(boost::string_view directory, boost::system::error_code &err);
};


#endif //THUNET_ASUS_KEEPALIVE_USER_SETTINGS_HPP