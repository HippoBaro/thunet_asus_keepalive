#include <utility>

//
// Created by Hippolyte Barraud on 10/13/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_PERIODIC_TASK_HPP
#define THUNET_ASUS_KEEPALIVE_PERIODIC_TASK_HPP

#include <boost/asio/io_context.hpp>
#include <boost/noncopyable.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/asio.hpp>
#include <logger.hpp>

struct periodic_task : boost::noncopyable {
protected:
    periodic_task(boost::asio::io_context &ctx);
    void log(boost::string_view, log_level = log_level::info);

public:
    virtual ~periodic_task() = default;

    virtual int task(boost::asio::io_context &ctx) = 0;
    virtual boost::string_view name() = 0;

private:
    void execute(boost::system::error_code const &e);

    void start();

    boost::asio::io_context &io_context;
    boost::asio::deadline_timer timer;
};


#endif //THUNET_ASUS_KEEPALIVE_PERIODIC_TASK_HPP
