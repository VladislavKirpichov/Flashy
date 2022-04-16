#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>

#include "responce.h"
#include "request.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


class HTTP_nahdler : public std::enable_shared_from_this<HTTP_nahdler> {
public:
    HTTP_nahdler(tcp::socket&& socket) : ws(std::move(socket)) {}

    void run() {
        ws.async_accept([self{shared_from_this()}](beast::error_code ec){
            if (ec) {
                std::cout << ec.message() << std::endl;
                return;
            }

            self->http();
        });
    }

    void http() {
        ws.async_read(buffer, [self{shared_from_this()}](beast::error_code ec,
                                                        std::size_t bytes_transfered)
        {
            if (ec == websocket::error::closed) return;
            if (ec) {
                std::cout << ec.message() << std::endl;
                return;
            }

            auto out = beast::buffers_to_string(self->buffer.cdata());

            if (out == "get") {
                self->buffer.clear();
                self->buffer.reserve(sizeof(Response));

                Response res;
                res.body = "<h1>rew</h1>\r\n";
                ;
            }

            self->ws.async_write(self->buffer.data(), [self](beast::error_code ec,
                                                    std::size_t bytes_transfered)
            {
                if (ec == websocket::error::closed) return;
                if (ec) {
                    std::cout << ec.message() << std::endl;
                    return;
                }

                self->buffer.consume(self->buffer.size());
            });

            // self->buffer.clear();
            self->http();
        });
    }

private:
    websocket::stream<beast::tcp_stream> ws;    // ws- web stream
    beast::flat_buffer buffer;
};