//
// Created by Hippolyte Barraud on 10/14/18.
//

#include <tunet.hpp>
#include "keepalive_task.hpp"

namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost


keepalive_task::keepalive_task(boost::asio::io_context &ioc, user_settings const &settings) : periodic_task(ioc),
                                                                                              settings(settings) {}

int keepalive_task::task(boost::asio::io_context &ioc) {
    boost::system::error_code ec;

    auto connection_status = tunet::status(ioc, ec);
    if (ec) {
        log("Got error: " + ec.message(), log_level::error);
        return 20;
    }

    if (connection_status) {
        log("You are online " + connection_status->username);
    }
    else {
        auto login_attempt = tunet::login(ioc, settings.accounts, ec);
        if (ec) {
            log("Got error: " + ec.message(), log_level::error);
            return 20;
        }
        else {
            log("You are now logged on, " + login_attempt->operator[]<boost::string_view>("username")->to_string());
        }
    }

    return 120;
}

boost::string_view keepalive_task::name() {
    return "TUNet-Keepalive";
}

keepalive_task::~keepalive_task() {

}
