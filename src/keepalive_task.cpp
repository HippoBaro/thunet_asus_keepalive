//
// Created by Hippolyte Barraud on 10/14/18.
//

#include "keepalive_task.hpp"

namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

//keepalive_task::keepalive_task(std::weak_ptr<user_settings> usr) {

//}
