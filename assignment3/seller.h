#ifndef ASSIGNMENT3_SELLER_H
#define ASSIGNMENT3_SELLER_H

#include <queue>
#include "customer.h"
#include "concert.h"

class Seller {
public:
	
	char type;
	int  id;
	
	Concert *concert;
	
	std::queue<Customer> eventQueue;
	
	Seller(char type, int id);
	
	void customerArrives(Customer &customer);
	
	// print events that happen during the time slice
	void timeSlice(int time);

private:
	
	std::queue<Customer> customerQueue;
	
	bool findSeat(Customer &customer);
	
};

#endif //ASSIGNMENT3_SELLER_H
