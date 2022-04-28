// Simple client for TEST ONLY
// Build: g++ client.cpp -o client -pthread

#include <boost/beast/core.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace http = boost::beast::http;


class Client {
public:
    static void getResponce(std::string host, unsigned short port) {
        net::io_context ioc;
        net::ip::tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        auto const results = resolver.resolve(host, std::to_string(port));
        stream.connect(results);

        http::request<http::string_body> req(http::verb::get, "/text/html/", 11);

        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        http::write(stream, req);

        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        std::cout << res << std::endl;

        stream.socket().shutdown(net::ip::tcp::socket::shutdown_both);
    }
};

int main(int argc, char* argv[]) {
    auto const host = argv[1];
    auto const port = std::atoi(argv[2]);
    Client::getResponce(host, port);
}