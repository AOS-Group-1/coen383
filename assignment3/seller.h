#ifndef ASSIGNMENT3_SELLER_H
#define ASSIGNMENT3_SELLER_H

#include <queue>
#include "customer.h"

class Seller {
	
	char type;
	int  id;
	
	std::queue<Customer> queue;
	
	Seller(char type, int id);
	
	void customerArrives(Customer &customer);
	
	// print events that happen during the time slice
	void timeSlice(int time);
	
};

#endif //ASSIGNMENT3_SELLER_H
