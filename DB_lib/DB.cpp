#include "DB.h"

void DB::Connect(std::string ip, std::string port,
	std::string username, std::string password) {
    try {
		this->driver = get_driver_instance();
		this->con = driver->connect("tcp://" + ip + ":" + port + "", username, password);
	}catch (sql::SQLException & e) {
		std::cout << "# ERR: " << e.what();
	}
}

void DB::Close() {
    try {
		delete this->prep_stmt;
		delete this->con;
		delete this->res;
	}catch (sql::SQLException & e) {
		std::cout << "# ERR: " << e.what();
	}
}

void DB::Execute(std::string query) {
    try {
		this->stmt = this->con->createStatement();
		this->stmt->execute(query);
	} catch (sql::SQLException & e) {
		std::cout << "# ERR: " << e.what();
    }
}

std::vector <std::vector<std::string>>
DB::Execute(std::string query, int RowSize) {
    std::vector <std::string> tmp;
	std::vector <std::vector<std::string>> tmp2;
	try {
		this->stmt = this->con->createStatement();
		this->res = this->stmt->executeQuery(query);
		while (res->next()) {
			for (int a = 1; a != RowSize + 1; a++)
				tmp.push_back(res->getString(a));
			tmp2.push_back(tmp);
			tmp.clear();
		}
	}catch (sql::SQLException & e) {
		std::cout << "# ERR: " << e.what();
	}
	return tmp2;
}

void DB::Execute_Query(std::string query, std::vector<std::string> params) {
	try {
		prep_stmt = con->prepareStatement(query);

		int b = 1;
		for (int a = 0; a < params.size(); a++) {
			if (!params[a].find("S:"))
				prep_stmt->setString(b, params[a].substr(2, params[a].length()));
			else if (!params[a].find("I:"))
				prep_stmt->setInt(b, atoi(params[a].substr(2, params[a].length()).c_str()));
			b++;
		}

		prep_stmt->execute();
	} catch (sql::SQLException & e) {
		std::cout << "# ERR: " << e.what();
	}
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
    std::vector<std::vector<std::string>> ree;
	std::vector <std::string> tmp;
	std::vector <std::vector<std::string>> tmp2;
	try {
		prep_stmt = con->prepareStatement(query);
		int b = 1;
		for (int a = 0; a < params.size(); a++) {
			if (!params[a].find("S:"))
				prep_stmt->setString(b, params[a].substr(2, params[a].length()));
			else if (!params[a].find("I:"))
				prep_stmt->setInt(b, atoi(params[a].substr(2, params[a].length()).c_str()));
			b++;
		}
		try {
			this->res = prep_stmt->executeQuery();
			while (res->next()) {
				for (int a = 1; a != RowSize + 1; a++)
					tmp.push_back(res->getString(a));
				tmp2.push_back(tmp);
				tmp.clear();
			}
		} catch (sql::SQLException & e) {
			std::cout << "# ERR: " << e.what();
		}
	} catch (sql::SQLException & e) {
		std::cout << "# ERR: " << e.what();
	}
	return tmp2;
}

std::vector<std::vector<std::string>>
DB::Get(std::string query, int RowSize) {
	std::vector <std::string> tmp;
	std::vector <std::vector<std::string>> tmp2;
	try {
		prep_stmt = con->prepareStatement(query);
		try {
			this->res = prep_stmt->executeQuery();
			while (res->next()) {
				for (int a = 1; a != RowSize + 1; a++)
					tmp.push_back(res->getString(a));
				tmp2.push_back(tmp);
				tmp.clear();
			}
		} catch (sql::SQLException & e) {
			std::cout << "# ERR: " << e.what();
		}
	} catch (sql::SQLException & e) {
		std::cout << "# ERR: " << e.what();
	}
	return tmp2;
}

DB::DB(std::string ip, std::string port,
std::string username, std::string password, std::string DBname) {
	try {
		this->driver = get_driver_instance();
		this->con = driver->connect("tcp://" + ip + ":" + port + "", username, password);
		this->con->setSchema(DBname);
	}catch (sql::SQLException & e) {
		std::cout << "# ERR: " << e.what();
	}
}

DB::DB(){
	try {
		this->driver = get_driver_instance();
	}catch (sql::SQLException & e) {
		std::cout << "# ERR: " << e.what();
	}
}







