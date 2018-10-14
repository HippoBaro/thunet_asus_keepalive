//
// Created by Hippolyte Barraud on 10/14/18.
//

#include <boost/asio.hpp>
#include <logger.hpp>
#include <user_settings.hpp>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include "user_settings.hpp"
#include <logger.hpp>


namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

user_settings::user_settings(boost::string_view json, boost::system::error_code &err) : json_object(json, err) {
    if (err) {
        logger_("Error while reading setting JSON: " + json.to_string(), log_level::error);
        return;
    }

    auto arr = this->operator[]<JsonValue>("accounts");
    if (arr) {
        for (auto node : *arr) {
            auto account = json_object(node->value);
            accounts.emplace_back(*account.operator[]<boost::string_view>("username"), *account.operator[]<boost::string_view>("password"));
        }
        logger_("Successfully read accounts");
    }
}

user_settings::user_settings() {}

user_settings user_settings::make_from_fs(boost::system::error_code &err) {
    logger_("Locating setting file...", log_level::debug);

    boost::string_view directory;
#ifndef __DEV__
        char path[4096];
        ssize_t count = readlink("/proc/self/exe", path, 4096);
        if (count == -1) {
            err = boost::system::errc::make_error_code(boost::system::errc::no_such_file_or_directory);
            return user_settings();
        }
        directory = dirname(path);
#else
        directory = "/Users/hbarraud";
#endif

    logger_("Reading setting file at " + (std::string(directory) + "/settings.json"), log_level::info);
    FILE *f = fopen((std::string(directory) + "/settings.json").data(), "rb");
    if (!f) {
        logger_((std::string(directory) + "/settings.json") + " does not exits. Creating empty setting.", log_level::info);
        return user_settings();
    }
    fseek(f, 0, SEEK_END);
    auto fsize = static_cast<size_t>(ftell(f));
    rewind(f);

    std::string content(fsize + 1, '\0');
    fread(const_cast<char *>(content.data()), fsize, 1, f); //work around GCC 6 bug
    fclose(f);

    return user_settings(content, err);
}