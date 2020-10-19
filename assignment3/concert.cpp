#include "concert.h"
#include <pthread.h>

Concert::Concert() {
    Concert::seatMutex = PTHREAD_MUTEX_INITIALIZER;
}

bool Concert::allocateSeat(Customer &customer, int row, int column) {
    if(pthread_mutex_trylock(&seatMutex) == 0) {
        return false;
    }
    pthread_mutex_lock(&seatMutex);
    seats[row][column] = &customer;
    pthread_mutex_unlock(&seatMutex);
    return true;
}

bool Concert::isRowFull(int row) {
    for(int column = 0; column < 10; column++) {
        if(seats[row][column] == nullptr) {
            return false;
        }
    }
    return true;
}

bool Concert::isFull() {
    for(int row = 0; row < 10; row++) {
        if(!isRowFull(row)) {
            return false;
        }
    } 
    return true;
}