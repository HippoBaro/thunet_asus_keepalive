//
// Created by Hippolyte Barraud on 10/14/18.
//

#include <boost/asio.hpp>
#include <logger.hpp>
#include <user_settings.hpp>
#include <logger.hpp>


namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

user_settings::user_settings(boost::string_view json, boost::system::error_code &err) : json_object(json, err) {
    if (err) {
        logger_->operator()("Error while reading setting JSON: " + json.to_string(), log_level::error);
        return;
    }

    auto arr = this->operator[]<JsonValue>("accounts");
    if (arr) {
        for (auto node : *arr) {
            auto account = json_object(node->value);
            accounts.emplace_back(*account.operator[]<boost::string_view>("username"),
                                  *account.operator[]<boost::string_view>("password"));
        }
        logger_->operator()("Successfully read " + std::to_string(accounts.size()) + " accounts");
    }
}

user_settings::user_settings() {}

std::unique_ptr<user_settings>
user_settings::make_from_fs(boost::string_view directory, boost::system::error_code &err) {
    logger_->operator()("Locating setting file...", log_level::debug);

    logger_->operator()("Reading setting file at " + (std::string(directory) + "/tunet_settings.json"),
                        log_level::info);
    FILE *f = fopen((std::string(directory) + "/settings.json").data(), "rb");
    if (!f) {
        logger_->operator()((std::string(directory) + "/settings.json") + " does not exits. Creating empty setting.",
                            log_level::info);
        return std::make_unique<user_settings>();
    }
    fseek(f, 0, SEEK_END);
    auto fsize = static_cast<size_t>(ftell(f));
    rewind(f);

    std::string content(fsize + 1, '\0');
    fread(const_cast<char *>(content.data()), fsize, 1, f); //work around GCC 6 bug
    fclose(f);

    return std::make_unique<user_settings>(content, err);
}