
#include "Client.h"

HTTPClient::HTTPClient(net::io_context &ioc):
resolver(ioc), ws(ioc), stream(ioc){}

std::string HTTPClient::get_response(const std::string& host, const unsigned short& port, const std::string& target) {
    auto const results = resolver.resolve(host, std::to_string(port));
    stream.connect(results);

    //http::request<http::string_body> req(http::verb::get, "/user?login=test_user", 11);
    http::request<http::string_body> req(http::verb::get, target, 11);

    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(stream, req);

    http::response<http::string_body> res;
    http::read(stream, buffer, res);
    stream.socket().shutdown(net::ip::tcp::socket::shutdown_both);
    return res.body();
}
