#ifndef DB_LIB_DB_H_
#define DB_LIB_DB_H_
#include <vector>
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


class DB {
	protected:
		sql::Driver            *driver;
		sql::Connection        *con;
		sql::Statement         *stmt;
		sql::ResultSet         *res;
		sql::PreparedStatement *prep_stmt;

	private:
		void Execute_Query(std::string,
			std::vector<std::string>);

	public:

		DB(std::string, std::string,
			std::string, std::string, std::string);
		
		DB();

		void Execute(std::string);

		std::vector<std::vector<std::string>>
			Execute(std::string, int);

		void Close();

		void Connect(std::string, std::string,
				std::string, std::string);

		void Insert(std::string, std::vector<std::string>);

		std::vector<std::vector<std::string>>
			Get(std::string, std::vector<std::string>, int);

		std::vector<std::vector<std::string>>
			Get(std::string, int);

		void Update(std::string, std::vector<std::string>);

		void Delete(std::string, std::vector<std::string>);

	};




#endif  // UTILS_LIB_UTILS_H_