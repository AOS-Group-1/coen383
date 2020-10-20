#ifndef ASSIGNMENT3_SELLER_H
#define ASSIGNMENT3_SELLER_H

#include <queue>
#include "customer.h"
#include "concert.h"

class Seller {
public:
	
	char type;
	int  id;
	
	std::queue<Customer *> eventQueue;
	std::queue<Customer *> customerQueue;
	
	Seller(char type, int id);
	
	void customerArrives(Customer *customer, int time);
	
	// print events that happen during the time slice
	void timeSlice(int time);

private:
	
	bool findSeat(Customer *customer) const;
	
};

#endif //ASSIGNMENT3_SELLER_H
