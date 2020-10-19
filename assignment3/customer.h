#ifndef ASSIGNMENT3_CUSTOMER_H
#define ASSIGNMENT3_CUSTOMER_H

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdlib.h>
#include <time.h>

class Customer {
public:
	std::string id;
	int arrivalTime;
	int serviceTime;
	int responseTime;
	int turnaroundTime;
	int waitingTime;
	
};

bool cmp(Customer a, Customer b);
void generate_customers(int n, std::queue <Customer> &customers_queue, char customer_type);

#endif //ASSIGNMENT3_CUSTOMER_H
