#include "database.h"

const string Database::localhost = "localhost";
const string Database::defaultUser = "root";

Database::Database(const string& _db, const string& pwd, const string& _host,
	const string& _user, const string& _charset): 
	db(_db), password(pwd), host(_host), username(_user), charset(_charset) {}

SqlConn Database::getConn()
{
	MYSQL* mysql = new MYSQL;
	//初始化数据库
	mysql_init(mysql);
	//设置字符编码
	mysql_options(mysql, MYSQL_SET_CHARSET_NAME, charset.c_str());
	if (!mysql_real_connect(mysql, host.c_str(),
		username.c_str(), password.c_str(),
		db.c_str(), port, NULL, 0))
	{
		delete mysql;
		SqlConn conn(NULL);
		conn.setError();
		return conn;
	}
	return SqlConn(mysql);
}