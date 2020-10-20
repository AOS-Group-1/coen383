#ifndef ASSIGNMENT3_CONCERT_H
#define ASSIGNMENT3_CONCERT_H

#include "customer.h"
#include "seller.h"
class Seller;

typedef struct {
    std::string seller;
    bool assigned;
    Customer customer;
} Seat;

class Concert {
private:
    static Concert *instance;
    // Private Constructor so that no objects can be created
    Concert();

	Seat        *seats[10][10];
	pthread_mutex_t locks[10][10];
	//ticket_lock_t *lock;
public:
    /*typedef struct ticket_lock {
        pthread_cond_t cond;
        pthread_mutex_t mutex;
        unsigned long queue_head, queue_tail;
    } ticket_lock_t;

    void initLock();
    void ticket_lock();
    void ticket_unlock();*/
    static Concert *getInstance(){
        if(!instance)
            instance = new Concert;
        return instance;
    }

    // returns false if could not set seat
    bool allocateSeat(Customer &customer, Seller *seller, int row);

    void printSeats();

    bool isFull();
    bool isRowFull(int row);

};

#endif //ASSIGNMENT3_CONCERT_H
