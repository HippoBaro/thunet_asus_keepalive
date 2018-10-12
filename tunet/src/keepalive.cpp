//
// Created by Hippolyte Barraud on 10/10/18.
//

#include <cstdlib>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/asio/connect.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/field.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/http/read.hpp>
#include <payloads/challenge_response.hpp>
#include <payloads/login_request.hpp>
#include <error_code.hpp>
#include <payloads/challenge_request.hpp>
#include <payloads/login_response.hpp>

namespace boost {
    inline void throw_exception(std::exception const &) {
        std::abort();
    }

} // namespace boost

constexpr auto thu_network_host = "auth4.tsinghua.edu.cn";

template<typename Request, typename Response>
static boost::optional<Response>
post(boost::string_view target, boost::asio::ip::tcp::socket &socket, Request const &request,
     boost::system::error_code &ec) {
    boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::post, target, 11};
    req.set(boost::beast::http::field::host, thu_network_host);
    req.set(boost::beast::http::field::content_type, "application/x-www-form-urlencoded");
    req.set(boost::beast::http::field::accept,
            "text/javascript, application/javascript, application/ecmascript, application/x-ecmascript, */*; q=0.01");

    req.body() = request.to_form_urlencoded();
    req.prepare_payload();

    boost::beast::http::request_serializer<boost::beast::http::string_body> s{req};
    boost::beast::http::write(socket, s, ec);
    if (ec) {
        return {};
    }

    boost::beast::flat_buffer buffer;
    boost::beast::http::response<boost::beast::http::string_body> res;
    boost::beast::http::read(socket, buffer, res, ec);
    if (ec) {
        return {};
    }

    if (res.result() != boost::beast::http::status::ok) {
        ec = boost::beast::errc::make_error_code(boost::beast::errc::protocol_error);
        return {};
    }

    auto response = Response(res.body(), ec);
    if (ec) {
        return {};
    }
    return response;
}

namespace tunet {
    void
    keepalive(boost::asio::io_context &ioc, std::vector<std::pair<boost::string_view, boost::string_view>> credentials,
              boost::system::error_code &ec) noexcept {
        boost::asio::ip::tcp::resolver resolver{ioc};
        auto const hosts = resolver.resolve(thu_network_host, "http", ec);
        if (ec) {
            return;
        }

        boost::asio::ip::tcp::socket socket{ioc};
        boost::asio::connect(socket, hosts.begin(), hosts.end(), ec);
        if (ec) {
            return;
        }

        for (const auto &credential : credentials) {
            tunet::payloads::challenge_request challenge_req(credential.first, "");
            auto token = post<payloads::challenge_request, payloads::challenge_response>("/cgi-bin/get_challenge",
                                                                                         socket, challenge_req, ec);
            if (ec || !token) {
                return;
            }

            auto request = tunet::payloads::login_request(credential.first, credential.second, "", *token->operator[]<boost::string_view>("challenge"));
            auto response = post<payloads::login_request, payloads::login_response>("/cgi-bin/srun_portal", socket,
                                                                                    request, ec);
            if (ec) {
                return;
            }
            if (response) {
                break;
            }
        }

        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        if (ec) {
            return;
        }
    }
}