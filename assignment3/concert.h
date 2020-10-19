#ifndef ASSIGNMENT3_CONCERT_H
#define ASSIGNMENT3_CONCERT_H

#include "customer.h"

class Concert {
public:
	/*typedef struct ticket_lock {
		pthread_cond_t cond;
		pthread_mutex_t mutex;
		unsigned long queue_head, queue_tail;
	} ticket_lock_t;

	void initLock();
	void ticket_lock();
	void ticket_unlock();*/
	
	Concert();
	
	// returns false if could not set seat
	bool allocateSeat(Customer &customer, int row);
	
	void printSeats();
	
	bool isFull();
	bool isRowFull(int row);

private:
	Customer *seats[10][10] = {{nullptr}};
	pthread_mutex_t *locks[10][10];
	//ticket_lock_t *lock;
};

#endif //ASSIGNMENT3_CONCERT_H
