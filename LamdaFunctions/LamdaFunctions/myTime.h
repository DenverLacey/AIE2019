#pragma once
class myTime
{
public:
	myTime();
	myTime(long long time, char* name);
	~myTime();

	long long time;
	char* name;
};

