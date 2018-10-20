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


keepalive_task::keepalive_task(boost::asio::io_context &ioc, user_settings const &settings) :
        periodic_task(ioc), settings(settings), current_account(std::begin(settings.accounts)) {
}


bool
keepalive_task::login_account(boost::asio::io_context &ioc, boost::string_view username, boost::string_view password,
                              boost::system::error_code &ec) {
    log("Trying to login as " + username.to_string(), log_level::debug);
    auto login_attempt = tunet::login(ioc, username, password, ec);
    if (ec) {
        log("Login failed: " + ec.message(), log_level::error);
        return false;
    }
    log("Checking if account has internet access...", log_level::debug);
    auto connection_status = tunet::status(ioc, ec);
    if (ec) {
        log("Fetching connection status failed: " + ec.message(), log_level::error);
    }
    if (!connection_status) {
        log("Account doesn't have internet access", log_level::debug);
        return false;
    }
    return true;
}

std::pair<keepalive_task::keepalive_sleep, bool>
keepalive_task::account_roundrobin(boost::asio::io_context &ioc, boost::system::error_code &ec) {
    log("Finding currently logged in user", log_level::debug);
    auto user = tunet::whoami(ioc, ec);
    if (ec) {
        log("Fetching currently logged in user failed: " + ec.message(), log_level::error);
        return std::make_pair(keepalive_sleep::long_sleep, true);
    }

    if (user) {
        log("Fetching connection status for account " + *user, log_level::debug);
        auto connection_status = tunet::status(ioc, ec);
        if (ec) {
            log("Fetching connection status failed: " + ec.message() + ". Assuming no internet access",
                log_level::error);
            ec.clear();
        }

        if (connection_status) {
            log("Currently online with internet access as " + connection_status->username, log_level::debug);
            return std::make_pair(keepalive_sleep::long_sleep, true);
        }
        else {
            log("Not online. Logging out " + *user, log_level::debug);
            tunet::logout(ioc, *user, ec);
            if (ec) {
                log("Logout failed: " + ec.message(), log_level::error);
                return std::make_pair(keepalive_sleep::long_sleep, true);
            }
            return std::make_pair(keepalive_sleep::short_sleep, false);
        }
    }
    else {
        if (current_account >= std::end(settings.accounts)) {
            current_account = std::begin(settings.accounts);
        }

        log("No account currently logged in, trying " + current_account->first.to_string(), log_level::debug);

        if (login_account(ioc, current_account->first, current_account->second, ec)) {
            log("Successfully logged in as " + current_account->first.to_string(), log_level::info);
            return std::make_pair(keepalive_sleep::long_sleep, true);
        }
        log("Account " + current_account->first.to_string() +
            " does not have internet access. Retrying with next account...", log_level::info);
        ++current_account;
        return std::make_pair(keepalive_sleep::short_sleep, false);
    }
}


int keepalive_task::task(boost::asio::io_context &ioc) {
    boost::system::error_code ec;
    auto res = account_roundrobin(ioc, ec);
    if (!res.second) {
        previous_sleep = 0;
        return static_cast<int>(res.first);
    } else if (previous_sleep >= 5 * static_cast<int>(res.first)) {
        return previous_sleep;
    } else {
        previous_sleep += 2 * static_cast<int>(res.first);
        return previous_sleep;
    }
}

boost::string_view keepalive_task::name() {
    return "TUNetKeepalive";
}

keepalive_task::~keepalive_task() {

}