#include "DB.h"

void DB::Connect(std::string ip, std::string port,
	std::string username, std::string password) {
        
}

void DB::Close() {

}

void DB::Execute(std::string query) {

}

std::vector <std::vector<std::string>>
DB::Execute(std::string query, int RowSize) {
    std::vector <std::vector<std::string>> data = {{"a"},{"b"},{"c"}};
    return data;
}

void DB::Execute_Query(std::string query, std::vector<std::string> params) {

}

void DB::Insert(std::string query, std::vector<std::string> params) {
	this->Execute_Query(query, params);
}

void DB::Update(std::string query, std::vector<std::string> params) {
	this->Execute_Query(query, params);
}

void DB::Delete(std::string query, std::vector<std::string> params) {
	this->Execute_Query(query, params);
}

std::vector<std::vector<std::string>>
DB::Get(std::string query, std::vector<std::string> params, int RowSize) {
    std::vector <std::vector<std::string>> data = {{"a"},{"b"},{"c"}};
    return data;
}

std::vector<std::vector<std::string>>
DB::Get(std::string query, int RowSize) {
    std::vector <std::vector<std::string>> data = {{"a"},{"b"},{"c"}};
    return data;
}

DB::DB(std::string ip, std::string port,
std::string username, std::string password, std::string DBname) {

}

DB::DB(){

}







