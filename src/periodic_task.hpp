#include <utility>

//
// Created by Hippolyte Barraud on 10/13/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_PERIODIC_TASK_HPP
#define THUNET_ASUS_KEEPALIVE_PERIODIC_TASK_HPP

#include <chrono>
#include <boost/asio/io_context.hpp>
#include <boost/noncopyable.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/asio.hpp>

struct periodic_task : boost::noncopyable {
    periodic_task(boost::asio::io_context &ctx, boost::string_view const &name, std::chrono::seconds interval,
                  std::function<void(boost::system::error_code &err)> task);

    void execute(boost::system::error_code const &e);

    void start();

private:
    void start_wait();

    boost::asio::io_context &io_context;
    boost::asio::deadline_timer timer;
    std::function<void(boost::system::error_code &err)> task;
    std::string name;
    int interval;
};


#endif //THUNET_ASUS_KEEPALIVE_PERIODIC_TASK_HPP
