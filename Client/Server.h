#ifndef RECSYS_CLIENT_SERVER_H_
#define RECSYS_CLIENT_SERVER_H_

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>



// Performs an HTTP GET and prints the response
class Server : public std::enable_shared_from_this<Server>
{
  tcp::resolver resolver_;
  beast::tcp_stream stream_;
  beast::flat_buffer buffer_; // (Must persist between reads)
  http::request<http::empty_body> req_;
  http::response<http::string_body> res_;

 public:

  // Objects are constructed with a strand to
  // ensure that handlers do not execute concurrently.
  explicit Server(net::io_context& ioc)
      : resolver_(net::make_strand(ioc))
      , stream_(net::make_strand(ioc))
  {
  }

  // Start the asynchronous operation
  void run(
      char const* host,
      char const* port,
      char const* target,
      int version);

  void on_resolve(
      beast::error_code ec,
      tcp::resolver::results_type results);

  void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type);

  void on_write(beast::error_code ec,
      std::size_t bytes_transferred);

  void on_read(
      beast::error_code ec,
      std::size_t bytes_transferred);
};


#endif //RECSYS_CLIENT_SERVER_H_
