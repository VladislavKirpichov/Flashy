#include "listener.h"

#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>

#include "HTTP_handler.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// Accepts incoming connections and launches the sessions
class Listener : public std::enable_shared_from_this<Listener> {
public:
    Listener(net::io_context& ioc, const unsigned short port)
    : ioc(ioc), acceptor(ioc, {net::ip::make_address("127.0.0.1"), port}) {}

    void asyncAccept() {
        acceptor.async_accept(ioc, [self{shared_from_this()}](boost::system::error_code ec,
        tcp::socket socket){
            std::make_shared<HTTP_nahdler>(std::move(socket))->run();
            std::cout << "connection accepted" << std::endl;
            self->asyncAccept();
        });
    }

private:
    net::io_context& ioc;
    tcp::acceptor acceptor;
};