/*
	Assignment:	Course Project
	Author:		Andrew Engel
	Date:		01/23/18
	Filename:	Main.cpp
	Purpose:	Entry point of the course project bank reception simulator
*/

#include "stdafx.h"
#include "Customer.h"
#include "Clock.h"
#include "ReportLog.h"
#include <string>
#include <queue>
#include <array>
#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

//function definitions
void assignTeller(Customer& cust);
void printLogs(vector<ReportLog>);
void processTranMinutes();
void logDetails(queue<Customer> t1, queue<Customer> t2, queue<Customer> t3);
vector<ReportLog> logArrival(vector<ReportLog>&, Customer*);
vector<ReportLog> sortLogs(vector<ReportLog>&);
stack<Customer> createCustomers();
bool checkCustomerArrival();
int getBankCustomers();

//test functions
void testRandomGenerator();						//in main()
void testCustomers(array<Customer, 20> custs);	//in main()
void testTellerAssignment(int teller);			//in assignTeller() function
void testProcessTranMinutes();					//in main() while loop
void testLogDetails(queue<Customer> t1, queue<Customer> t2, queue<Customer> t3);	//in main() while loop, but also see commented lines in printLogs() function

//global variables
queue<Customer> teller1;
queue<Customer> teller2;
queue<Customer> teller3;

int main()
{
	srand(time(0));
	Clock clock(10, 1);
	stack<Customer> customers = createCustomers();
	vector<ReportLog> logs;
	//program loop
	while (!customers.empty() && clock.withinBusinessHours())
	{
		clock.incrementMinute();
		if (checkCustomerArrival())
		{
			Customer c = customers.top();
			Customer* cptr = &c;
			c.setArrival(clock.getCurrentTime());
			logArrival(logs, cptr);

			assignTeller(c);
			//remove customer from pre-created stack
			customers.pop();
		}

		//testLogDetails(teller1, teller2, teller3); //***REMOVE COMMENT TO TEST*** (may also want to uncomment test lines in printLogs() function)
		logDetails(teller1, teller2, teller3);

		//testProcessTranMinutes();  //***REMOVE COMMENT TO TEST***
		processTranMinutes();
	}
	//end of day, print report
	cout << left << setw(12) << "Last Name";
	cout << setw(20) << "Transaction Type";
	cout << setw(16) << "Arrival";
	cout << "Currency" << endl;
	printLogs(logs);

	//run tests
	//testRandomGenerator();		//***REMOVE COMMENT TO TEST***
	//testCustomers(customers);		//***REMOVE COMMENT TO TEST***
	
	int pause;
	cin >> pause;
    return 0;
}

void assignTeller(Customer& cust)
{
	int teller = 0; //testing purposes
	//assign customer to teller
	int ttlCusts = getBankCustomers();
	if (ttlCusts < 4)
	{
		teller1.push(cust);
		teller = 1;
	}
	else if (ttlCusts < 8)
	{
		teller2.push(cust);
		teller = 2;
	}
	else
	{
		teller3.push(cust);
		teller = 3;
	}

	//testTellerAssignment(teller);		//***REMOVE COMMENT TO TEST***
}

void printLogs(vector<ReportLog> logs)
{
	//sort records and print each
	logs = sortLogs(logs);
	for each (ReportLog record in logs)
	{
		record.printRecord();
	}
	//print averages
	double avgWait = double(ReportLog::totalWaitTimes) / ReportLog::totalMinutes;
	int avgCustomers = ReportLog::customersWaitingPerMin / ReportLog::totalMinutes;

	//***UNCOMMENT NEXT TWO LINES FOR TESTING***
	//cout << "\nAverage Wait Times Calculation: " << ReportLog::totalWaitTimes << " / " << ReportLog::totalMinutes << endl;
	//cout << "Average Customers Waiting Calculation: " << ReportLog::customersWaitingPerMin << " / " << ReportLog::totalMinutes << endl;

	cout << "\nAverage Waiting Times: " << avgWait << " minutes" << endl;
	cout << "Average Customers Waiting: " << avgCustomers << endl;
}

//if there are customers in the bank, 
//decrement trans minutes of each customer at the front of each queue
void processTranMinutes()
{
	if (getBankCustomers() > 0)	
	{
		if (!teller1.empty())
		{
			teller1.front().decrementTranMinutes();
			if (teller1.front().getTranMinutes() == 0)
			{
				teller1.pop();
			}
		}
		if (!teller2.empty())
		{
			teller2.front().decrementTranMinutes();
			if (teller2.front().getTranMinutes() == 0)
			{
				teller2.pop();
			}
		}
		if (!teller3.empty())
		{
			teller3.front().decrementTranMinutes();
			if (teller3.front().getTranMinutes() == 0)
			{
				teller3.pop();
			}
		}
	}
}

void logDetails(queue<Customer> t1, queue<Customer> t2, queue<Customer> t3)
{
	ReportLog::incrementTotalMin();
	ReportLog::accumCustsWaitingPerMin(getBankCustomers());

	if (getBankCustomers() > 0)
	{
		int ttlTranTimes = 0;
		while (!t1.empty())
		{
			ttlTranTimes += t1.front().getTranMinutes();
			t1.pop();
		}
		while (!t2.empty())
		{
			ttlTranTimes += t2.front().getTranMinutes();
			t2.pop();
		}
		while (!t3.empty())
		{
			ttlTranTimes += t3.front().getTranMinutes();
			t3.pop();
		}

		ttlTranTimes /= getBankCustomers();		//calculate average wait times per this minute
		ReportLog::accumTotalWaitTimes(ttlTranTimes);
	}	
}

vector<ReportLog> logArrival(vector<ReportLog>& logs, Customer* cust)
{
	//create new log
	logs.push_back(ReportLog(cust->getLastName(), cust->getTransType(), cust->getArrivalTime(), cust->getTranMoney()));
	ReportLog::incrementTotalNewCusts();
	return logs;
}

vector<ReportLog> sortLogs(vector<ReportLog>& logs)
{
	ReportLog temp;
	for (int i = 0; i < logs.size() - 1; i++)
	{
		if (logs[i].getLastName() > logs[i + 1].getLastName())
		{
			temp = logs[i];
			logs[i] = logs[i + 1];
			logs[i + 1] = temp;
			i = -1;		//reset iteration
		}
	}
	return logs;
}

stack<Customer> createCustomers()
{
	stack<Customer> custs;
	custs.push(Customer("Bill", "Newman", "Deposit", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Carol", "Johnson", "Open", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Tim", "Williams", "Deposit", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Fred", "Thompson", "Close", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Mary", "Schaefer", "Deposit", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Joe", "Nelson", "Withdrawal", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Matthew", "Corbin", "Withdrawal", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Janice", "Topper", "Open", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Miranda", "Watts", "Deposit", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Sarah", "Clavette", "Close", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Geoffry", "Sinks", "Deposit", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Kevin", "Knuth", "Withdrawal", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Persey", "Jackson", "Withdrawal", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Steve", "Hart", "Deposit", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Cloe", "Ellis", "Deposit", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Naomi", "Morris", "Withdrawal", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Phil", "Chapman", "Close", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Calvin", "Porter", "Withdrawal", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Nellie", "Franklin", "Deposit", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Mariah", "Stevens", "Withdrawal", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Fred", "Jacobson", "Withdrawal", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Jimmy", "Slye", "Close", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Bailey", "Palecheck", "Deposit", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Kelly", "Cartwright", "Deposit", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Mike", "Turnpike", "Open", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Allen", "Ward", "Open", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Carley", "Marley", "Withdrawal", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Dan", "Zastrow", "Deposit", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Joshua", "Todd", "Deposit", 1 + rand() % 20, 50 + rand() % 550));
	custs.push(Customer("Amy", "Everest", "Withdrawal", 1 + rand() % 20, 50 + rand() % 550));

	return custs;
}

bool checkCustomerArrival()
{
	int probability = 1 + rand() % 10;

	//20% chance a customer arrives
	if (probability == 1 || probability == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//returns total number of customers in the bank
int getBankCustomers()
{
	int custs = 0;
	custs = teller1.size() + teller2.size() + teller3.size();
	return custs;
}

//***TEST FUNCTIONS****

void testRandomGenerator()
{
	int probability = 0;
	for (size_t i = 0; i < 100; i++)
	{
		probability = 1 + rand() % 10;
		cout << probability << endl;
		if (probability > 10 || probability < 1)
		{
			cout << "***RAND OUTSIDE OF RANGE***" << endl;
		}
	}
}

void testCustomers(array<Customer, 20> custs)
{
	for each (Customer person in custs)
	{
		cout << person.getFirstName() << " " << person.getLastName() << " " << person.getTransType() << " " << person.getTranMinutes() << " " << person.getTranMoney() << endl;
	}
}

void testTellerAssignment(int teller)
{
	cout << "Bank Customers: " << getBankCustomers() << "  Teller Assigned: " << teller << endl;
}

void testProcessTranMinutes()
{
	if (getBankCustomers() > 0)
	{
		if (!teller1.empty())
		{
			teller1.front().decrementTranMinutes();
			cout << teller1.front().getFirstName() << " Minutes left: " << teller1.front().getTranMinutes() << endl;
			if (teller1.front().getTranMinutes() == 0)
			{
				teller1.pop();
				cout << "***CUSTOMER TRANSACTION COMPLETE - REMOVED FROM TELLER 1***" << endl;
			}
		}
		if (!teller2.empty())
		{
			teller2.front().decrementTranMinutes();
			cout << teller2.front().getFirstName() << " Minutes left: " << teller2.front().getTranMinutes() << endl;
			if (teller2.front().getTranMinutes() == 0)
			{
				teller2.pop();
				cout << "***CUSTOMER TRANSACTION COMPLETE - REMOVED FROM TELLER 2***" << endl;
			}
		}
		if (!teller3.empty())
		{
			teller3.front().decrementTranMinutes();
			cout << teller3.front().getFirstName() << " Minutes left: " << teller3.front().getTranMinutes() << endl;
			if (teller3.front().getTranMinutes() == 0)
			{
				teller3.pop();
				cout << "***CUSTOMER TRANSACTION COMPLETE - REMOVED FROM TELLER 3***" << endl;
			}
		}
	}
}

void testLogDetails(queue<Customer> t1, queue<Customer> t2, queue<Customer> t3)
{
	ReportLog::incrementTotalMin();
	ReportLog::accumCustsWaitingPerMin(getBankCustomers());

	if (getBankCustomers() > 0)
	{
		int ttlTranTimes = 0;
		while (!t1.empty())
		{
			ttlTranTimes += t1.front().getTranMinutes();
			cout << "Teller1: " << t1.front().getTranMinutes() << " min" << endl;
			t1.pop();
		}
		while (!t2.empty())
		{
			ttlTranTimes += t2.front().getTranMinutes();
			cout << "Teller2: " << t2.front().getTranMinutes() << " min" << endl;
			t2.pop();
		}
		while (!t3.empty())
		{
			ttlTranTimes += t3.front().getTranMinutes();
			cout << "Teller3: " << t3.front().getTranMinutes() << " min" << endl;
			t3.pop();
		}

		cout << ttlTranTimes << " / " << getBankCustomers() << endl;
		ttlTranTimes /= getBankCustomers();		//calculate average wait times per this minute
		ReportLog::accumTotalWaitTimes(ttlTranTimes);
	}
}