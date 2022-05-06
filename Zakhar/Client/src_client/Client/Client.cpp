
#include "Client.h"

WebSocketClient::WebSocketClient(net::io_context &ioc):
resolver(ioc), ws(ioc), stream(ioc){}
void WebSocketClient::Connect(std::string &host, std::string &port){
    auto const results = resolver.resolve(host, port);
    auto ep = net::connect(ws.next_layer(), results);

    host += ':' + std::to_string(ep.port());

    ws.set_option(websocket::stream_base::decorator(
            [](websocket::request_type& req)
            {
                req.set(http::field::user_agent,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
            }));

    ws.handshake(host, "/");
}
void WebSocketClient::Write(std::string text){
    ws.write(net::buffer(std::string(text)));
}
void WebSocketClient::Read(){
    ws.read(buffer);
}
void WebSocketClient::Disconnect(){
    ws.close(websocket::close_code::normal);
}
void WebSocketClient::data_to_string(){
    std::cout << beast::make_printable(buffer.data());
}
void WebSocketClient::getResponce(std::string host, unsigned short port) {
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
