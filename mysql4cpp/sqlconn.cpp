#include "sqlConn.h"
#include "sqlresult.h"

void close(MYSQL* sql)
{
	mysql_close(sql);
	printf("MYSQL connection %p closed\n", sql);
	delete sql;
}

void stmt_close(MYSQL_STMT* stmt)
{
	mysql_stmt_close(stmt);
	printf("statement %p closed\n", stmt);
}

SqlConn::SqlConn(MYSQL* sql): 
	ptr(unique_ptr<MYSQL, CloseFunc>(sql, close)) {}

SqlConn::SqlConn(SqlConn&& conn) :
	ptr(conn.ptr.release(), close),
	error(conn.error) {}

MYSQL* SqlConn::get()
{
	return ptr.get();
}

bool SqlConn::isOpen()
{
	return ptr.get() != NULL;
}

void SqlConn::setError()
{
	const char* err = mysql_error(ptr.get());
	error = string(err);
}

string SqlConn::getError()
{
	return error;
}

Statement SqlConn::prepareStatment(const string& sql)
{
	return Statement(mysql_stmt_init(ptr.get()), sql);
}

ResultSet SqlConn::executeQuery(const string& sql)
{
	mysql_real_query(ptr.get(), sql.c_str(), sql.length());
	MYSQL_RES* res = mysql_store_result(ptr.get());
	if (res == nullptr)
		return ResultSet(nullptr, false);
	return ResultSet(new SqlResult(res), true);
}

unsigned long long SqlConn::executeUpdate(const string& sql)
{
	mysql_real_query(ptr.get(), sql.c_str(), sql.length());
	return mysql_affected_rows(ptr.get());
}
