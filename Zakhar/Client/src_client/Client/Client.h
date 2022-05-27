

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H
#include <iostream>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = boost::beast::http;// from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;
class HTTPClient{
public:
    explicit HTTPClient(net::io_context &ioc);
    std::string get_response(const std::string& host,const unsigned short& port, const std::string& target);
    bool post_request(const std::string& host, const unsigned short& port, const std::string& target,
                             const std::string& body);
    bool put_request(const std::string& host, const unsigned short& port, const std::string& target,
                      const std::string& body);
    bool delete_request(const std::string& host, const unsigned short& port,const std::string& target);

private:
    tcp::resolver resolver;
    beast::tcp_stream stream;
    beast::flat_buffer buffer;

};
#endif //CLIENT_CLIENT_H
