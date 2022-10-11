# mysql4cpp
mysql api的c++简单封装

目前实现basic的sql查询和预编译sql的执行

**Usage：**

创建连接

```c++
Database db("db_name", "your_database_password", "localhost", "your_database_userame");
SqlConn conn = db.getConn();
if (!conn.isOpen())
    printf("connect error: %s\n", conn.getError().c_str());
```

执行普通sql查询

```c++
string sql = "select * from user";
ResultSet rs = conn.executeQuery(sql);
if(rs.isValid())
	while (rs.hasNext())
	{
		rs.next();
		printf("id: %d, name: %s\n", rs.getInt(1), rs.getString(2).c_str());
	}


string sql = "update user set create_time = NOW() where name = 'jeff'";
int affected = conn.executeUpdate(sql);
printf("%d rows affected\n", affected);
```

执行预编译的查询

```c++
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

Statement stmt = conn.prepareStatment("insert into user(name, create_time) values(?, NOW()), (?, NOW()), (?, NOW()), (?, NOW())");
stmt.setString(1, "rose");
stmt.setString(2, "john");
stmt.setString(3, "mary");
stmt.setString(4, "jeff");
int affected = stmt.executeUpdate();
if (affected)
	printf("rows affected: %d\n", affected);
else
	cout << stmt.getError() << endl;
```



#### 进度

- ~~实现basic api封装~~
- ~~实现预编译sql封装~~
- ~~实现日期封装~~
- ~~实现连接池~~
- ~~事务支持~~

