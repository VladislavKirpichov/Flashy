#include "Manager.h"
Manager::Manager(net::io_context &ioc): client(WebSocketClient(ioc))
{}
void Manager::Connect(std::string &host, std::string &port){
client.Connect(host, port);
}
void Manager::Auth(std::string Login, std::string Password){}
void Manager::Reg(std::string Login, std::string Password){}
void Manager::Get_Page(std::string page_id){}
void Manager::Update(std::string Update_message){}
void Manager::Exit(){
    client.Disconnect();
}
void Manager::ChangeUser(const User & new_user){
    current_user = new_user;
}