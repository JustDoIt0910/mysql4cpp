#pragma once
#include <memory>
#include <mysql.h>
#include <string>
#include <iostream>
#include "statement.h"
using namespace std;

typedef void (*CloseFunc)(MYSQL*);

class SqlConn
{
public:
	SqlConn(MYSQL* mysql);
	SqlConn(SqlConn&& conn);
	SqlConn(SqlConn&) = delete;

	MYSQL* get();
	bool isOpen();
	void setError();
	string getError();
	Statement prepareStatment(const string& sql);
	ResultSet executeQuery(const string& sql);
	unsigned long long executeUpdate(const string& sql);

private:
	unique_ptr<MYSQL, CloseFunc> ptr;
	string error;
};

