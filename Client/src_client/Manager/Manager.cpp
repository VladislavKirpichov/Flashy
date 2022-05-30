#include "Manager.h"

Manager::Manager(net::io_context &ioc) : client(HTTPClient(ioc)) {}

std::string Manager::get(const std::string &target) {
    return client.get_response(host, port, target);
}

bool Manager::post(const std::string &target, const std::string &body, const std::string & type) {
    return client.post_request(host, port, target, body, type);
}

std::string Manager::put(const std::string &target, std::string &body) {
    return client.put_request(host, port, target, body);
}

bool Manager::_delete(const std::string &target) {
    return client.delete_request(host, port, target);
}

void Manager::get_user_from_server(const std::string &login, const std::string &password) {
    std::string target = "/user/?login=" + login + "&password=" + password;
    std::string gt = get(target);
    current_user = serializer.user_deserialize(gt);
}

void Manager::get_page_from_server(const std::string &page_id) {
    current_questions.clear();
    std::string target = "/page/?page_id=" + page_id;
    current_page = serializer.page_deserialize(get(target));
    std::string _text = get(target + "&content=true");
    _text.erase(_text.size() - 1);
    current_page.set_text(_text);
    get_questions_from_page();
}

Question Manager::get_question_from_server(const int &question_id) {
    std::string target =
            "/question/?question_id=" + std::to_string(question_id) + "&page_id=" + std::to_string(current_page.get_id());
    return serializer.question_deserialize(get(target));
}

void Manager::get_questions_from_page() {
    current_questions.clear();
    for (int i = 0; i < current_page.get_questions_id().size(); ++i) {
        Question temp = get_question_from_server(current_page.get_questions_id()[i]);
        current_questions.push_back(temp);
    }
}

bool Manager::create_page_to_server(const std::string &title) {
    std::string target = "/page/?login=" + current_user.get_login();
    current_page = Page();
    current_page.set_title(title);
    current_page.set_user_id(current_user.get_id());
    std::string request = serializer.page_serialize(current_page);
    std::string json = put(target, request);
    std::cout << json;
    if (json == "Bad Request 400\n") {
        return false;
    }
    current_page = serializer.page_deserialize(json);
    std::cout << request << '\n';
    return true;
}

std::string Manager::create_question_to_server() {
    std::string target = "/question/?page_id=" + std::to_string(current_page.get_id()); //page_id в JSON
    Question temp = Question(current_page.get_id());
    std::string request = serializer.question_serialize(temp);
    std::cout << request << '\n';
   return put(target,request);
}

bool Manager::change_user_in_server() {
    std::string target = "/user/?login=" + current_user.get_login() + "&password=" + current_user.get_password();
    if (post(target, serializer.user_serialize(current_user),"application/json"))
        return true;
    else
        return false;
}

bool Manager::change_page_in_server() {
    std::string target = "/page/?page_id=" + current_page.get_page_id();
    std::cout << serializer.page_serialize(current_page) << "\n";
    if (post(target, serializer.page_serialize(current_page),"application/json") &&
        post(target + "&content=true", current_page.get_text(),"text/text")) {
//        if (change_question_from_page())
//            return true;
//        else
//            return false;
    }
    return false;
}

bool Manager::change_question_to_server(const int &question_index) {
    std::string target =
            "/question/?question_id=" + std::to_string(current_questions[question_index].get_question_id()) +
            "&page_id= " + std::to_string(current_page.get_id());
    std::string request =  serializer.question_serialize(current_questions[question_index]);
    std::cout << request << "\n";
    if (post(target,request,"application/json")) {
        return true;
    } else
        return false;
}

bool Manager::change_question_from_page() {
    for (int i = 0; i < current_page.get_questions_id().size(); ++i) {
        if (!change_question_to_server(i))
            return false;
    }
    return true;
}

bool Manager::auth(const std::string &login, const std::string &password) {
    std::string target = "/auth/?login=" + login + "&password=" + password;
    if (get(target) == "ok\n")
        return true;
    return false;
}

bool Manager::reg(const std::string &name, const std::string &login, const std::string &password,
                  const std::string &email) {
    User new_user;
    new_user.set_login(login);
    new_user.set_password(password);
    new_user.set_name(name);
    new_user.set_email(email);
    new_user.set_status("Status");
    std::string request = serializer.user_serialize(new_user);
    std::cout << request << '\n';
    std::string target = "/signup/?login=" + login + "&password=" + password;
    if (put(target, request) == "ok\n")
        return true;
    else
        return false;
}


User &Manager::get_user() {
    return current_user;
}

Page &Manager::get_page() {
    return current_page;
}

std::vector<Question> &Manager::get_questions() {
    return current_questions;
}


void Manager::set_destination(const std::string &new_host, const unsigned short &new_port) {
    host = new_host;
    port = new_port;
}
