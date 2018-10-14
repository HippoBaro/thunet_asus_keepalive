//
// Created by Hippolyte Barraud on 10/13/18.
//

#include "periodic_scheduler.hpp"

namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

void periodic_scheduler::addTask(boost::asio::io_context &ctx, boost::string_view name,
                                 std::function<void(boost::system::error_code &)> const &task,
                                 std::chrono::seconds interval) {
    tasks.push_back(std::make_unique<periodic_task>(std::ref(ctx), name, interval, task));
}
