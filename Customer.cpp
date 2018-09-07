/*
Assignment:	Course Project
Author:		Andrew Engel
Date:		01/23/18
Filename:	Customer.cpp
Purpose:	Provide implementations of the Customer class
*/

#include "stdafx.h"
#include "Customer.h"
#include <string>

using namespace std;

Customer::Customer()
{
}


Customer::~Customer()
{
}

void Customer::decrementTranMinutes()
{
	if (transactionMinutes > 0)
	{
		transactionMinutes--;
	}
	else
	{
		transactionMinutes = 0;
	}
}

void Customer::setArrival(string time)
{
	arrivalTime = time;
}

string Customer::getFirstName() const
{
	return firstName;
}

string Customer::getLastName() const
{
	return lastName;
}

string Customer::getArrivalTime() const
{
	return arrivalTime;
}

string Customer::getTransType() const
{
	return transactionType;
}

int Customer::getTranMinutes() const
{
	return transactionMinutes;
}

double Customer::getTranMoney() const
{
	return transactionMoney;
}