#ifndef ASSIGNMENT3_CUSTOMER_H
#define ASSIGNMENT3_CUSTOMER_H

#include <string>

class Customer {
public:
	std::string id;
	int arrivalTime;
	int serviceTime;
	int responseTime;
	int turnaroundTime;
	int waitingTime;
	
};

#endif //ASSIGNMENT3_CUSTOMER_H
