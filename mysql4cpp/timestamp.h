#pragma once
#include <time.h>
#include <mysql.h>
#include <string>
#include <vector>
using namespace std;


class Timestamp
{
public:
	typedef enum TimeUnit
	{
		microsecond = 0,
		second,
		minute,
		hour,
		day,
		month,
		year
	} TimeUnit;

	typedef enum ParseResult
	{
		success = 0,
		fail
	} ParseResult;

	Timestamp(time_t time);
	Timestamp(const string& timeStr);
	Timestamp(const string& timeStr, const string& format);
	Timestamp(const MYSQL_TIME* mysqlTime);

	void addTime(int value, Timestamp::TimeUnit unit);
	void addSeconds(double seconds);
	string toFormattedString();
	MYSQL_TIME toMysqlTime();
	bool isValid();

	static Timestamp now();
	static Timestamp::ParseResult parseTimeStr(const string& str, struct tm* _tm);
	const static int microSecondsPerSecond = 1000 * 1000;
	
private:
	//Internal
	time_t microSecondsSinceEpoch;
	Timestamp();
	
};

string strip(const string& str);
vector<string> split(const string& str, const string& sep);