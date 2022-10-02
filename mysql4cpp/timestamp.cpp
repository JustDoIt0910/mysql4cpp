#include "timestamp.h"
#include <chrono>


Timestamp::Timestamp(time_t time): microSecondsSinceEpoch(time) {}

Timestamp::Timestamp() : microSecondsSinceEpoch(0) {}

bool Timestamp::isValid()
{
	return microSecondsSinceEpoch > 0;
}

Timestamp::Timestamp(const string& timeStr)
{
	struct tm _tm;
	memset(&_tm, 0, sizeof(_tm));
	ParseResult r = parseTimeStr(timeStr, &_tm);
	if (r != success)
	{
		microSecondsSinceEpoch = 0;
		return;
	}
	microSecondsSinceEpoch = mktime(&_tm);
}

Timestamp::Timestamp(const string& timeStr, const string& format)
{
}

Timestamp::Timestamp(const MYSQL_TIME* mysqlTime)
{
}

void Timestamp::addTime(int value, Timestamp::TimeUnit unit)
{
}

void Timestamp::addSeconds(double seconds)
{
}

string Timestamp::toFormattedString()
{
	if (!isValid())
		return string();
	char buf[25];
	memset(buf, 0, sizeof(buf));
	struct tm _tm;
	memset(&_tm, 0, sizeof(_tm));
	time_t t = microSecondsSinceEpoch / microSecondsPerSecond;
	localtime_s(&_tm, &t);
	sprintf_s(buf, "%04d-%02d-%02d %02d:%02d:%02d",
		_tm.tm_year + 1900, _tm.tm_mon + 1, _tm.tm_mday, _tm.tm_hour, _tm.tm_min, _tm.tm_sec);
	return string(buf);
}

MYSQL_TIME Timestamp::toMysqlTime()
{
	return MYSQL_TIME();
}

Timestamp Timestamp::now()
{
	return Timestamp(
		static_cast<time_t>(
			chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count()
		)
	);
}

Timestamp::ParseResult Timestamp::parseTimeStr(const string& str, struct tm* _tm)
{
	string time = strip(str);
	size_t spaceIdx = time.find(' ');
	size_t ymdLen = spaceIdx != string::npos ? spaceIdx : str.length();
	string ymdtPart = time.substr(0, ymdLen);
	vector<string> ymd = split(ymdtPart, "-/");
	if (ymd.size() != 3 || ymd[0].length() != 4)
		return fail;
	_tm->tm_year = stoi(ymd[0]) - 1900;
	_tm->tm_mon = stoi(ymd[1]) - 1;
	if (_tm->tm_mon < 0 || _tm->tm_mon > 11)
		return fail;
	_tm->tm_mday = stoi(ymd[2]);
	if (_tm->tm_mday < 1 || _tm->tm_mday > 31)
		return fail;
	if (spaceIdx != string::npos)
	{
		size_t hourPos = spaceIdx + 1;
		while (isspace(time.at(hourPos)))
			hourPos++;
		vector<string> hms = split(time.substr(hourPos), ":");
		size_t sz = hms.size();
		if (sz == 0)
			return success;
		_tm->tm_hour = stoi(hms[0]);
		if (_tm->tm_hour > 24 || _tm->tm_hour < 0)
			return fail;
		if (sz > 1)
		{
			_tm->tm_min = stoi(hms[1]);
			if (_tm->tm_min > 59 || _tm->tm_min < 0)
				return fail;
		}
		if (sz > 2)
		{
			_tm->tm_sec = stoi(hms[2]);
			if (_tm->tm_sec > 59 || _tm->tm_sec < 0)
				return fail;
		}
	}
	return success;
}

string strip(const string& str)
{
	int i = 0;
	int j = str.size() - 1;
	if (j < i)
		return string();
	while (i < j && isspace(str.at(i)))
		i++;
	if (i == j)
		return string();
	while (j > i && isspace(str.at(j)))
		j--;
	return str.substr(i, j - i + 1);
}

vector<string> split(const string& str, const string& seps)
{
	vector<string> arr;
	size_t l = 0; size_t r = 0;
	while (l < str.size())
	{
		r = str.find_first_of(seps, l);
		if (r == l)
		{
			l++;
			continue;
		}
		if (r == string::npos)
		{
			arr.push_back(str.substr(l));
			break;
		}
		arr.push_back(str.substr(l, r - l));
		l = r + 1;
	}
	return arr;
}