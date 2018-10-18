//
// Created by Hippolyte Barraud on 10/13/18.
//

#include <boost/bind.hpp>
#include "periodic_task.hpp"
#include <logger.hpp>

namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

periodic_task::periodic_task(boost::asio::io_context &ctx) : io_context(ctx), timer(ctx) {
    io_context.post(boost::bind(&periodic_task::start, this));
}


void periodic_task::execute(boost::system::error_code const &e) {
    if (e != boost::asio::error::operation_aborted) {
        start();
    }
}

void periodic_task::start() {
    int interval = task(io_context);
    if (interval > 0) {
        log("Sleeping for " + std::to_string(interval) + " seconds", log_level::debug);
        timer.expires_from_now(boost::posix_time::seconds(interval));
        timer.async_wait(boost::bind(&periodic_task::execute, this, boost::asio::placeholders::error));
    }
    else {
        log("Stopping periodic task");
    }
}

void periodic_task::log(boost::string_view log, log_level level) {
    logger_->operator()("[" + name().to_string() + "] " + log.to_string(), level);
}
