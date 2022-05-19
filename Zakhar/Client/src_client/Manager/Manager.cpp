#include "Manager.h"
Manager::Manager(net::io_context &ioc): client(HTTPClient(ioc))
{}
std::string Manager::get_json(const std::string& host,const unsigned short& port){
   return  client.get_response(host, port);
}

void Manager::Auth(std::string Login, std::string Password){}
void Manager::Reg(std::string Login, std::string Password){}
void Manager::Get_Page(std::string page_id){}
void Manager::Update(std::string Update_message){}
void Manager::ChangeUser(const User & new_user){
    current_user = new_user;
}