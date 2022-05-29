#include "Client.h"

HTTPClient::HTTPClient(net::io_context &ioc):
resolver(ioc), stream(ioc){}

std::string HTTPClient::get_response(const std::string& host, const unsigned short& port, const std::string& target) {
    auto const results = resolver.resolve(host, std::to_string(port));
    stream.connect(results);

    http::request<http::string_body> req(http::verb::get, target, 11);

    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(stream, req);

    http::response<http::string_body> res;
    http::read(stream, buffer, res);
    stream.socket().shutdown(net::ip::tcp::socket::shutdown_both);
    return res.body();
}
bool HTTPClient::post_request(const std::string& host, const unsigned short& port, const std::string& target,
                         const std::string& body){
    auto const results = resolver.resolve(host, std::to_string(port));
    stream.connect(results);
    http::request<http::string_body> req(http::verb::post, target, 11);
    req.set(http::field::body, body);
    req.prepare_payload();
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.prepare_payload();

    http::write(stream, req);

    http::response<http::string_body> res;
    http::read(stream, buffer, res);
    stream.socket().shutdown(net::ip::tcp::socket::shutdown_both);
    std::string result=  res.body();
    if(result == "ok\n"){
        return true;
    }
    else
        return false;

}
std::string HTTPClient::put_request(const std::string& host, const unsigned short& port, const std::string& target,
                            const std::string& body){
    auto const results = resolver.resolve(host, std::to_string(port));
    stream.connect(results);

    http::request<http::string_body> req(http::verb::put, target, 11);
    req.set(http::field::content_type, "application/json");
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.body() = body;
    req.prepare_payload();

    http::write(stream, req);

    http::response<http::string_body> res;
    http::read(stream, buffer, res);
    stream.socket().shutdown(net::ip::tcp::socket::shutdown_both);
    std::string result=  res.body();
    return result;
}
bool HTTPClient::delete_request(const std::string& host, const unsigned short& port,const std::string& target){
    auto const results = resolver.resolve(host, std::to_string(port));
    stream.connect(results);

    http::request<http::string_body> req(http::verb::delete_, target, 11);

    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(stream, req);

    http::response<http::string_body> res;
    http::read(stream, buffer, res);
    stream.socket().shutdown(net::ip::tcp::socket::shutdown_both);
    std::string result=  res.body();
    if(result == "ok\n"){
        return true;
    }
    else
        return false;
}