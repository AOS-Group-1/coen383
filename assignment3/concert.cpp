#include "concert.h"
#include <pthread.h>
#include <iostream>

/*void Concert::initLock() {
    lock->cond = PTHREAD_COND_INITIALIZER;
    lock->mutex = PTHREAD_MUTEX_INITIALIZER;
}*/

Concert::Concert() {
	//initLock();
	for (auto &lock : locks) {
		for (auto &column : lock) {
			pthread_mutex_init(column, nullptr);
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
	for (auto &seat : seats) {
		for (auto &column : seat) {
			if (column != nullptr) {
				std::cout << column->id << ", ";
			} else {
				std::cout << "-, ";
			}
		}
		std::cout << "\n";
	}
}

bool Concert::allocateSeat(Customer &customer, int row) {
	for (int i = 0; i < 10; i++) {
		if (seats[row][i] == nullptr) {
			if (pthread_mutex_trylock(locks[row][i]) == 0) {
				seats[row][i] = &customer;
				pthread_mutex_unlock(locks[row][i]);
				printSeats();
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
