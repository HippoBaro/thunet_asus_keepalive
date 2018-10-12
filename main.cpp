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

    tunet::keepalive(ioc, {std::make_pair<boost::string_view>(av[1], av[2])}, ec);
    if (ec) {
        printf("Got error: %s\n", ec.message().data());
    }
    return EXIT_SUCCESS;
}