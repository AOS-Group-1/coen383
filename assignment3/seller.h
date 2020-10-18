#ifndef ASSIGNMENT3_SELLER_H
#define ASSIGNMENT3_SELLER_H

#include <queue>
#include "customer.h"

class Seller {
public:
	
	char type;
	int  id;
	
	Seller(char type, int id);
	
	void customerArrives(Customer &customer);
	
	// print events that happen during the time slice
	void timeSlice(int time);

private:
	
	std::queue<Customer> queue;
	
};

#endif //ASSIGNMENT3_SELLER_H
