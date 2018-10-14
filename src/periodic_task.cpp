//
// Created by Hippolyte Barraud on 10/13/18.
//

#include "periodic_task.hpp"
#include <boost/bind.hpp>

namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

periodic_task::periodic_task(boost::asio::io_context &ctx, boost::string_view const &name,
                             std::chrono::seconds interval, std::function<void(boost::system::error_code &err)> task) :
        io_context(ctx), timer(ctx), task(std::move(task)), name(name),
        interval(static_cast<int>(interval.count())) {
    io_context.post(boost::bind(&periodic_task::start, this));
}


void periodic_task::execute(boost::system::error_code const &e) {
    if (e != boost::asio::error::operation_aborted) {
        boost::system::error_code err;
        task(err);
        if (err) {
            //log
            return;
        }
        timer.expires_at(timer.expires_at() + boost::posix_time::seconds(interval));
        start_wait();
    }
}

void periodic_task::start() {
    //log_text("Start periodic_task '" + name + "'");

    boost::system::error_code err;
    task(err);
    if (err) {
        //log
        return;
    }
    timer.expires_from_now(boost::posix_time::seconds(interval));
    start_wait();
}

void periodic_task::start_wait() {
    timer.async_wait(boost::bind(&periodic_task::execute, this, boost::asio::placeholders::error));
}
