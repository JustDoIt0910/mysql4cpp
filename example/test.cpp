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
			printf("id: %d, name: %s\n", rs.getInt(1), rs.getString(2).c_str());
		}*/

	/*string sql = "update user set create_time = NOW() where name = 'jeff'";
	int affected = conn.executeUpdate(sql);
	printf("%d rows affected\n", affected);*/


    //using prepared statement
	Statement stmt = conn.prepareStatment("select * from user where name = ? or id = ?");
	stmt.setString(1, "jack");
	stmt.setInt(2, 7);
	ResultSet rs = stmt.executeQuery();
	if (rs.isValid())
	{
		while (rs.hasNext())
		{
			rs.next();
			int id = rs.getInt("id");
			string name = rs.getString("name");
			printf("id: %d, name: %s\n", id, name.c_str());
		}
	}
	else
		cout << stmt.getError() << endl;

	/*Statement stmt = conn.prepareStatment("insert into user(name, create_time) values(?, NOW()), (?, NOW()), (?, NOW()), (?, NOW())");
	stmt.setString(1, "rose");
	stmt.setString(2, "john");
	stmt.setString(3, "mary");
	stmt.setString(4, "jeff");
	int affected = stmt.executeUpdate();
	if (affected)
		printf("rows affected: %d\n", affected);
	else
		cout << stmt.getError() << endl;*/
	return 0;
}