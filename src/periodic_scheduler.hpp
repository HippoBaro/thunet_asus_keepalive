//
// Created by Hippolyte Barraud on 10/13/18.
//

#ifndef THUNET_ASUS_KEEPALIVE_PERIODIC_SCHEDULER_HPP
#define THUNET_ASUS_KEEPALIVE_PERIODIC_SCHEDULER_HPP

#include <chrono>
#include <boost/noncopyable.hpp>
#include <error_code.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/asio/io_context.hpp>
#include <periodic_task.hpp>

class periodic_scheduler : boost::noncopyable {
public:
    void addTask(boost::asio::io_context &ctx, std::unique_ptr<periodic_task> task);

private:
    std::vector<std::unique_ptr<periodic_task>> tasks;
};


#endif //THUNET_ASUS_KEEPALIVE_PERIODIC_SCHEDULER_HPP
