//
// Created by Hippolyte Barraud on 10/13/18.
//

#include <logger.hpp>
#include <boost/bind.hpp>
#include "periodic_scheduler.hpp"

namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

void periodic_scheduler::addTask(boost::asio::io_context &, std::unique_ptr<periodic_task> task) {
    logger_->operator()("Scheduling new periodic task " + task->name().to_string());
    tasks.emplace_back(std::move(task));
}
