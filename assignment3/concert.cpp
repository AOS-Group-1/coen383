#include <iostream>
#include "concert.h"

Concert *Concert::instance = nullptr;

Concert::Concert() {
	for (auto &row : seats)
		for (auto &col : row) {
			col = new Seat;
			col->assigned = false;
			col->customer = nullptr;
		}
	
	//initLock();
	for (auto &lock : locks) {
		for (auto &column : lock) {
			pthread_mutex_init(&column, nullptr);
		}
	}
}

void Concert::printSeats() {
	std::cout << "************************************************************\n";
	for (int row = 0; row < 10; row++) {
		for (int col = 0; col < 10; col++) {
			auto seat = seats[row][col];
			if (seat->assigned) {
				std::cout << "|" << seat->customer->id << "|";
			} else {
				std::cout << "|----|";
			}
		}
		std::cout << "\n";
	}
	std::cout << "************************************************************\n";
}

bool Concert::allocateSeat(Customer *customer, int row) {
	for (int i = 0; i < 10; i++) {
		if (!seats[row][i]->assigned) {
			if (pthread_mutex_trylock(&locks[row][i]) == 0) {
				seats[row][i]->customer = customer;
				seats[row][i]->assigned = true;
				pthread_mutex_unlock(&locks[row][i]);
//				printSeats();
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
