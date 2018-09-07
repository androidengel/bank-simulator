/*
Assignment:	Course Project
Author:		Andrew Engel
Date:		01/23/18
Filename:	Clock.cpp
Purpose:	Provide implementations of the Clock class to simulate bank hours and time passing
*/

#include "stdafx.h"
#include "Clock.h"
#include <string>

using namespace std;

Clock::Clock()
{
}

Clock::~Clock()
{
}

void Clock::incrementHour()
{
	if (hour < 12)
	{
		hour++;
	}
	else
	{
		hour = 1;
	}
}

void Clock::incrementMinute()
{
	if (minute < 59)
	{
		minute++;
	}
	else
	{
		minute = 0;
		incrementHour();
	}
}

string Clock::getCurrentTime()
{
	string hh = "";
	string mm = "";
	string time = "";

	//determine if trailing zero should be placed in front of minute and hour
	if (hour < 10)
	{
		hh = "0" + std::to_string(hour);
	}
	else
	{
		hh = std::to_string(hour);
	}

	if (minute < 10)
	{
		mm = "0" + std::to_string(minute);
	}
	else
	{
		mm = std::to_string(minute);
	}

	time = hh + ":" + mm;
	return time;
}

bool Clock::withinBusinessHours()
{
	if (hour < 10)
	{
		return false;
	}
	else
	{
		return true;
	}
}