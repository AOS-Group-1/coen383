#ifndef ASSIGNMENT3_SELLER_H
#define ASSIGNMENT3_SELLER_H

#include <queue>
#include "customer.h"

class Seller {
	
	char type;
	int  row;
	
	std::queue<Customer> queue;
	
	void customerArrives(Customer customer);
	
	// print events that happen during the time slice
	void timeSlice(int time);
	
};

#endif //ASSIGNMENT3_SELLER_H
