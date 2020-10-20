#include "concert.h"
#include <pthread.h>
#include <iostream>

/*void Concert::initLock() {
    lock->cond = PTHREAD_COND_INITIALIZER;
    lock->mutex = PTHREAD_MUTEX_INITIALIZER;
}*/

Concert::Concert() {

    for(auto &row : seats)
        for(auto &col : row){
            col = new Seat;
            col->assigned = false;
            //col.customer = new Customer;
        }



	//initLock();
	for (auto &lock : locks) {
		for (auto &column : lock) {
			pthread_mutex_init(&column, NULL);
		}
	}
}

/*void Concert::ticket_lock() {
    unsigned long queue;

    pthread_mutex_lock(&lock->mutex);
    queue = lock->queue_tail++;
    while(queue != lock->queue_head) {
        pthread_cond_wait(&lock->cond, &lock->mutex);
    }
    pthread_mutex_unlock(&lock->mutex);
}

void Concert::ticket_unlock() {
    pthread_mutex_lock(&lock->mutex);
    lock->queue_head++;
    pthread_cond_broadcast(&lock->cond);
    pthread_mutex_unlock(&lock->mutex);
}*/

void Concert::printSeats() {
    std::cout << "************************************************************\n";
    for(int row = 0; row < 10; row++){
        for(int col = 0; col < 10; col++){
            auto seat = seats[row][col];
            if(seat->assigned == true){
                std::cout << "|" << seat->seller + seat->customer.id << "|";
            }
            else{
                std::cout << "|----|";
            }
        }
        std::cout << "\n";
    }
    std::cout << "************************************************************\n";
}

bool Concert::allocateSeat(Customer &customer, Seller *seller, int row) {
	for (int i = 0; i < 10; i++) {
		if (seats[row][i]->assigned == false) {
			if (pthread_mutex_trylock(&locks[row][i]) == 0) {
				seats[row][i]->customer = customer;
                seats[row][i]->assigned = true;
                seats[row][i]->seller = seller->type + std::to_string(seller->id);
				pthread_mutex_unlock(&locks[row][i]);
				return true;
			}
		}
	}
	return false;
}

bool Concert::isRowFull(int row) {
	for (int column = 0; column < 10; column++) {
		if (seats[row][column] == nullptr) {
			return false;
		}
	}
	return true;
}

bool Concert::isFull() {
	for (int row = 0; row < 10; row++) {
		if (!isRowFull(row)) {
			return false;
		}
	}
	return true;
}
