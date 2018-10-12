#include <tunet.hpp>

namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <string>

namespace ip = boost::asio::ip;         // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio.hpp>
namespace http = boost::beast::http;    // from <boost/beast/http.hpp>

namespace my_program_state {
    std::size_t
    request_count() {
        static std::size_t count = 0;
        return ++count;
    }

    std::time_t
    now() {
        return std::time(0);
    }
}

class http_connection : public std::enable_shared_from_this<http_connection> {
public:
    http_connection(tcp::socket socket)
            : socket_(std::move(socket)) {
    }

    // Initiate the asynchronous operations associated with the connection.
    void
    start() {
        read_request();
        check_deadline();
    }

private:
    // The socket for the currently connected client.
    tcp::socket socket_;

    // The buffer for performing reads.
    boost::beast::flat_buffer buffer_{8192};

    // The request message.
    http::request<http::string_body > request_;

    // The response message.
    http::response<http::string_body> response_;

    // The timer for putting a deadline on connection processing.
    boost::asio::basic_waitable_timer<std::chrono::steady_clock> deadline_{
            socket_.get_executor().context(), std::chrono::seconds(60)};

    // Asynchronously receive a complete request message.
    void
    read_request() {
        auto self = shared_from_this();

        http::async_read(
                socket_,
                buffer_,
                request_,
                [self](boost::beast::error_code ec,
                       std::size_t bytes_transferred) {
                    boost::ignore_unused(bytes_transferred);
                    if (!ec) {
                        self->process_request();
                    }
                });
    }

    // Determine what needs to be done with the request message.
    void
    process_request() {
        response_.version(request_.version());
        response_.keep_alive(false);

        switch (request_.method()) {
            case http::verb::get:
                response_.result(http::status::ok);
                response_.set(http::field::server, "Beast");
                create_response();
                break;

            default:
                // We return responses indicating an error if
                // we do not recognize the request method.
                response_.result(http::status::bad_request);
                response_.set(http::field::content_type, "text/plain");
                response_.body() = "Invalid request-method '" + request_.method_string().to_string() + "'";
                break;
        }

        write_response();
    }

    // Construct a response message based on the program state.
    void
    create_response() {
        if (request_.target() == "/count") {
            response_.set(http::field::content_type, "text/html");
            response_.body() =  "<html>\n"
                                "<head><title>Request count</title></head>\n"
                                "<body>\n"
                                "<h1>Request count</h1>\n"
                                "<p>There have been " + std::to_string(my_program_state::request_count()) +
                                " requests so far.</p>\n"
                                "</body>\n"
                                "</html>\n";
        }
        else if (request_.target() == "/time") {
            response_.set(http::field::content_type, "text/html");
            response_.body() = "<html>\n"
                               "<head><title>Current time</title></head>\n"
                               "<body>\n"
                               "<h1>Current time</h1>\n"
                               "<p>The current time is " +
                               std::to_string(my_program_state::now()) +
                               " seconds since the epoch.</p>\n"
                               "</body>\n"
                               "</html>\n";
        }
        else {
            response_.result(http::status::not_found);
            response_.set(http::field::content_type, "text/plain");
           response_.body() = "File not found\r\n";
        }
    }

    // Asynchronously transmit the response message.
    void
    write_response() {
        auto self = shared_from_this();

        response_.set(http::field::content_length, response_.body().size());

        http::async_write(
                socket_,
                response_,
                [self](boost::beast::error_code ec, std::size_t) {
                    self->socket_.shutdown(tcp::socket::shutdown_send, ec);
                    self->deadline_.cancel();
                });
    }

    // Check whether we have spent enough time on this connection.
    void
    check_deadline() {
        auto self = shared_from_this();

        deadline_.async_wait(
                [self](boost::beast::error_code ec) {
                    if (!ec) {
                        // Close socket to cancel any outstanding operation.
                        self->socket_.close(ec);
                    }
                });
    }
};

// "Loop" forever accepting new connections.
void
http_server(tcp::acceptor &acceptor, tcp::socket &socket) {
    acceptor.async_accept(socket,
                          [&](boost::beast::error_code ec) {
                              if (!ec) {
                                  std::make_shared<http_connection>(std::move(socket))->start();
                              }
                              http_server(acceptor, socket);
                          });
}

int main(int ac, char **av) {
    boost::system::error_code ec;
    boost::asio::io_context ioc{1};

    auto const address = boost::asio::ip::make_address("0.0.0.0");
    unsigned short port = 80;

    tcp::acceptor acceptor{ioc, {address, port}, true};
    tcp::socket socket{ioc};
    http_server(acceptor, socket);

    ioc.run();

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