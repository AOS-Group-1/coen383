#ifndef ASSIGNMENT3_CUSTOMER_H
#define ASSIGNMENT3_CUSTOMER_H

#include <string>

class Seller;

class Customer {
public:
	std::string id;
	int         arrivalTime    = 0;
	int         serviceTime    = 0;
	int         responseTime   = -1;
	int         turnaroundTime = -1;
	int         waitingTime    = 0;
	
};

bool cmp(Customer *a, Customer *b);
void generate_customers(int n, Seller *seller);

#endif //ASSIGNMENT3_CUSTOMER_H
