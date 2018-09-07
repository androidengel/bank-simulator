#pragma once
/*
Assignment:	Course Project
Author:		Andrew Engel
Date:		01/23/18
Filename:	Customer.h
Purpose:	Provide definitions of the Customer class
*/

#include <string>

class Customer
{
public:
	Customer();
	Customer(std::string fName, std::string lName, std::string transType, int minutes, double money)
		: firstName(fName), lastName(lName), transactionType(transType), transactionMinutes(minutes), transactionMoney(money)
	{
	}
	~Customer();

	void decrementTranMinutes();
	void setArrival(std::string time);
	std::string getFirstName() const;
	std::string getLastName() const;
	std::string getArrivalTime() const;
	std::string getTransType() const;
	int getTranMinutes() const;
	double getTranMoney() const;

private:
	std::string firstName;
	std::string lastName;
	std::string arrivalTime;
	std::string transactionType;
	int transactionMinutes;
	double transactionMoney;
};

