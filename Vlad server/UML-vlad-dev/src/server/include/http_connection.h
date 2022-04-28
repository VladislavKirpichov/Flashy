//
// Created by vladislav on 25.04.22.
//

#ifndef SERVER_V0_1_HTTP_CONNECTION_H
#define SERVER_V0_1_HTTP_CONNECTION_H

#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>


class http_connection : public std::enable_shared_from_this<http_connection> {
public:
    http_connection(boost::asio::ip::tcp::socket socket);
    void run();

private:
    void read_request();

    // Generates a response depending on the request method.
    // Currently, supports only GET method !!!
    void process_request(boost::beast::error_code& ec, std::size_t bytes_transferred);

    // Creates response html
    void create_response();

    // Closes socket to cancel any outstanding operation
    void check_deadline();

    boost::asio::ip::tcp::socket _socket;
    boost::beast::flat_buffer _buffer{8192};
    boost::beast::http::request<boost::beast::http::dynamic_body> _request;
    boost::beast::http::response<boost::beast::http::dynamic_body> _response;

    // Timer for connection processing
    boost::asio::steady_timer _deadline{ _socket.get_executor(), std::chrono::seconds(60) };
};


#endif //SERVER_V0_1_HTTP_CONNECTION_H
