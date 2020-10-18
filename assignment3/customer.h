#ifndef ASSIGNMENT3_CUSTOMER_H
#define ASSIGNMENT3_CUSTOMER_H

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <ctime>

class Customer {
public:
	
	std::string id;
	
	int         arrivalTime    = 0;
	int         serviceTime    = 0;
	int         responseTime   = 0;
	int         turnaroundTime = 0;
	int         waitingTime    = 0;
};

bool cmp(Customer a, Customer b);
void generate_customers(int n, std::queue <Customer> &customers_queue);

#endif //ASSIGNMENT3_CUSTOMER_H
