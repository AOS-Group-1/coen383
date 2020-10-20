#ifndef ASSIGNMENT3_CONCERT_H
#define ASSIGNMENT3_CONCERT_H

#include "customer.h"

typedef struct {
	bool     assigned;
	Customer *customer;
} Seat;

class Concert {
private:
	static Concert *instance;
	// Private Constructor so that no objects can be created
	Concert();
	
	Seat            *seats[10][10]{};
	pthread_mutex_t locks[10][10]{};

public:
	
	static Concert *getInstance() {
		if (!instance)
			instance = new Concert;
		return instance;
	}
	
	// returns false if could not set seat
	bool allocateSeat(Customer *customer, int row);
	
	void printSeats();
	void printStats(int n, int time);
	
	bool isFull();
	bool isRowFull(int row);
	
};

#endif //ASSIGNMENT3_CONCERT_H
