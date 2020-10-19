#include "concert.h"
#include <pthread.h>



Concert::Concert() {
    Concert::seatMutex = PTHREAD_MUTEX_INITIALIZER;
}

Concert::bool allocateSeat(Customer &customer, int row, int column) {
    if(pthread_mutex_trylock(&seatMutex) == 0) {
        return false;
    }
    pthread_mutex_lock(&seatMutex);
    seats[row][column] = customer;
    pthread_mutex_unlock(&seatMutex);
    return true;
}

Concert::bool isRowFull(int row) {
    for(int column = 0; i < 10; i++) {
        if(seats[row][i] == nullptr) {
            return false;
        }
    }
    return true;
}

Concert::bool isFull() {
    for(int row = 0; row < 10; i++) {
        if(!isRowFull(row)) {
            return false;
        }
    } 
    return true;
}