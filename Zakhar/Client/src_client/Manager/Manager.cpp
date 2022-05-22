#include "Manager.h"
Manager::Manager(net::io_context &ioc): client(HTTPClient(ioc)){}
std::string Manager::get_json(const std::string& host,const unsigned short& port){
   return  client.get_response(host, port);
}
void Manager::get_user_from_server(const std::string& host,const unsigned short& port){
    current_user = serializer.user_deserialize(get_json(host, port));
}
void Manager::auth(std::string login, std::string password){}
void Manager::reg(std::string login, std::string password){}
void Manager::get_page(std::string page_id){}
void Manager::update(std::string update_message){}

User Manager::get_user()
{
    return current_user;
}
void Manager::change_user(const User & new_user){
    current_user = new_user;
}
