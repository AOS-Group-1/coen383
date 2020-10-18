#ifndef ASSIGNMENT3_CONCERT_H
#define ASSIGNMENT3_CONCERT_H

#include "customer.h"

class Concert {
	
	Customer seats[10][10];
	
	// returns false if could not set seat
	bool allocateSeat(Customer customer, int row, int column);
	
	int isFull();
	int isRowFull(int row);
	
};

#endif //ASSIGNMENT3_CONCERT_H
