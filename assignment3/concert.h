#ifndef ASSIGNMENT3_CONCERT_H
#define ASSIGNMENT3_CONCERT_H

#include "customer.h"

class Concert {
	
	Customer seats[10][10];
	
	pthread_mutex_t seatMutex;
	
	Concert();
	
	// returns false if could not set seat
	bool allocateSeat(Customer customer, int row, int column);
	
	bool isFull();
	bool isRowFull(int row);
	
};

#endif //ASSIGNMENT3_CONCERT_H
