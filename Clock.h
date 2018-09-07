#pragma once
/*
Assignment:	Course Project
Author:		Andrew Engel
Date:		01/23/18
Filename:	Clock.h
Purpose:	Provide definitions of the Clock class
*/

#include <string>

class Clock
{
public:
	Clock();
	Clock(int open, int close)
		: openTime(open), closeTime(close)
	{
		hour = open;
		minute = 0;
	}
	~Clock();

	void incrementHour();
	void incrementMinute();
	std::string getCurrentTime();
	bool withinBusinessHours();

private:
	int openTime;
	int closeTime;
	int hour;
	int minute;
};

