#include "myTime.h"



myTime::myTime() {}

myTime::myTime(long long time, const char name[]) {
	
	this->time = time;
	this->name = (char*)name;
}


myTime::~myTime() {}
