#include <database.h>
#include <resultset.h>
#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>

using namespace std;

int main()
{
	Database db("db_name", "your_database_password", "localhost", "your_database_userame");
	
	SqlConn conn = db.getConn();

	if (!conn.isOpen())
		printf("connect error: %s\n", conn.getError().c_str());

    //basic sql query and update

	/*string sql = "select * from user";
	ResultSet rs = conn.executeQuery(sql);
	if(rs.isValid())
		while (rs.hasNext())
		{
			rs.next();
			printf("id: %d, name: %s, create_time: %s\n", 
				rs.getInt(1), 
				rs.getString(2).c_str(), 
				rs.getTime(3).toFormattedString().c_str());
		}*/

	/*string sql = "update user set create_time = NOW() where name = 'jeff'";
	int affected = conn.executeUpdate(sql);
	printf("%d rows affected\n", affected);*/


    //using prepared statement
	
	Statement stmt = conn.prepareStatment("update user set create_time = ? where name = ?");
	stmt.setString(2, "james");
	Timestamp now = Timestamp::now();
	stmt.setTime(1, now, MYSQL_TYPE_TIMESTAMP);
	int affected = stmt.executeUpdate();
	if (affected)
		printf("rows affected: %d\n", affected);
	else
		cout << stmt.getError() << endl;

	Statement stmt2 = conn.prepareStatment("select * from user where name = ?");
	stmt2.setString(1, "james");
	ResultSet rs = stmt2.executeQuery();
	if (rs.isValid())
	{
		while (rs.hasNext())
		{
			rs.next();
			int id = rs.getInt("id");
			string name = rs.getString("name");
			Timestamp t = rs.getTime("create_time");
			printf("id: %d, name: %s, create_time: %s\n", id, name.c_str(), t.toFormattedString().c_str());
		}
	}
	else
		cout << stmt2.getError() << endl;
	return 0;
}