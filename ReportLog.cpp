/*
Assignment:	Course Project
Author:		Andrew Engel
Date:		01/23/18
Filename:	ReportLog.cpp
Purpose:	Provide implementations of the ReportLog class and track events so a report can be output for the bank simulation
*/

#include "stdafx.h"
#include "ReportLog.h"
#include <string>

using namespace std;

ReportLog::ReportLog()
{
}

ReportLog::~ReportLog()
{
}

//initialize static members
int ReportLog::totalMinutes = 0;
int ReportLog::customersWaitingPerMin = 0;
int ReportLog::totalNewCustomers = 0;
int ReportLog::totalWaitTimes = 0;

//static function
void ReportLog::accumTotalWaitTimes(int time)
{
	totalWaitTimes += time;
}

//static function
void ReportLog::incrementTotalNewCusts()
{
	totalNewCustomers++;
}

//static function
void ReportLog::accumCustsWaitingPerMin(int custs)
{
	customersWaitingPerMin += custs;
}

//static function
void ReportLog::incrementTotalMin()
{
	totalMinutes++;
}

void ReportLog::setLastName(string& name)
{
	lastName = name;
}

void ReportLog::setTranType(string& type)
{
	transactionType = type;
}

void ReportLog::setArrival(string& arrival)
{
	arrivalTime = arrival;
}

void ReportLog::setMoney(double money)
{
	this->money = money;
}

string ReportLog::getLastName() const
{
	return lastName;
}

string ReportLog::getTranType() const
{
	return transactionType;
}

string ReportLog::getArrival() const
{
	return arrivalTime;
}

double ReportLog::getMoney() const
{
	return money;
}

void ReportLog::printRecord()
{
	string ToD = "AM";
	if (arrivalTime > "11:59")
	{
		ToD = "PM";
	}
	cout << left << setw(12) << lastName;
	cout << setw(20) << transactionType;
	cout << arrivalTime << " " << setw(10) << ToD;
	cout << fixed << setprecision(2) << "$" << money << endl;
}