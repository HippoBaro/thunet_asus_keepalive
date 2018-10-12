#include <tunet.hpp>

namespace boost {
    inline void throw_exception(std::exception const&) {
        std::abort();
    }

} // namespace boost

int main(int ac, char** av)
{
    boost::system::error_code ec;
    boost::asio::io_context ioc;

    if (ac < 3) {
        return EXIT_FAILURE;
    }

    {
        auto connection_status = tunet::status(ioc, ec);
        if (ec) {
            printf("Got error: %s\n", ec.message().data());
        }

        if (connection_status) {
            printf("You are online, %s\n", connection_status->username.data());
            return EXIT_SUCCESS;
        }
    }

    {
        auto login_attempt = tunet::login(ioc, {std::make_pair<boost::string_view>(av[1], av[2])}, ec);
        if (ec) {
            printf("Got error: %s\n", ec.message().data());
        }
        else {
            printf("You are now logged on, %s\n", login_attempt->operator[]<boost::string_view>("username")->data());
        }
        return EXIT_SUCCESS;
    }

}