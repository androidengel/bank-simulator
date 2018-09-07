#pragma once
/*
Assignment:	Course Project
Author:		Andrew Engel
Date:		01/23/18
Filename:	ReportLog.h
Purpose:	Provide definitions of the ReportLog class
*/

#include <string>
#include <iostream>
#include <iomanip>

class ReportLog
{
public:
	ReportLog();
	ReportLog(std::string lName, std::string tranType, std::string arrival, double amount)
		: lastName(lName), transactionType(tranType), arrivalTime(arrival), money(amount)
	{
	};
	~ReportLog();
	static int ReportLog::totalWaitTimes;
	static int ReportLog::totalNewCustomers;
	static int ReportLog::customersWaitingPerMin;
	static int ReportLog::totalMinutes;
	static void accumTotalWaitTimes(int time);
	static void incrementTotalNewCusts();
	static void accumCustsWaitingPerMin(int custs);
	static void incrementTotalMin();
	void setLastName(std::string& name);
	void setTranType(std::string& type);
	void setArrival(std::string& arrival);
	void setMoney(double money);
	std::string getLastName() const;
	std::string getTranType() const;
	std::string getArrival() const;
	double getMoney() const;
	void printRecord();

private:
	std::string lastName;
	std::string transactionType;
	std::string arrivalTime;
	double money;

};

