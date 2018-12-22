#pragma once
class myTime
{
public:
	myTime();
	myTime(long long time, const char name[]);
	~myTime();

	long long time;
	char* name;
};

