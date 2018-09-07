# Bank Simulator
This program is designed to simulate a single business day of a bank reception. For each simulated minute of the work day, there is a 20% probability that a customer will enter the bank. If that happens, they are added to the queue as other customers are being serviced. Each customer has an assigned transaction and a random amount of time their transaction will take. Once the business day is complete, a log is printed to the console detailing all transactions, sorted by customer last name, as well as the average customer wait time and average number of customers waiting throughout the day.

This project was created for a college assignment. Its intent was to showcase the following competencies:
* Comprehension of data structures
* Pointers and references
* Unit testing
* Logging
* OOP
* UML diagramming
* Real-life simulation

Please see the Documents folder for the full project summary detail.

#### Note: this project was created in Visual Studio, which automatically creates stdafix files. These files have include statements in them, but the stdafix files are not in this repository. If using VS, create the C++ console application project before cloning this repo. If using a different IDE, you will need to remove the include statements.