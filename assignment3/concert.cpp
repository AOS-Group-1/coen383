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
	
	for (auto &lock : locks) {
		for (auto &column : lock) {
			pthread_mutex_init(&column, nullptr);
		}
	}
}

void Concert::printSeats() {
	std::cout << "************************************************************\n";
	for (auto &row : seats) {
		for (auto &seat : row) {
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

void Concert::printStats(int n, int time) {
	int   accepted_H = 0, accepted_M = 0, accepted_L = 0;
	int   rejected_H = 0, rejected_M = 0, rejected_L = 0;
	float art_H      = 0, art_M = 0, art_L = 0;
	float att_H      = 0, att_M = 0, att_L = 0;
	float awt_H      = 0, awt_M = 0, awt_L = 0;
	float atp_H      = 0, atp_M = 0, atp_L = 0;
	
	
	for (auto &seat : seats) {
		for (auto &c : seat) {
			if (c->assigned) {
				if (c->customer->id[0] == 'H') {
					accepted_H++;
					art_H += c->customer->responseTime;
					att_H += c->customer->turnaroundTime;
					awt_H += c->customer->waitingTime;
				} else if (c->customer->id[0] == 'M') {
					accepted_M++;
					art_M += c->customer->responseTime;
					att_M += c->customer->turnaroundTime;
					awt_M += c->customer->waitingTime;
					
				} else if (c->customer->id[0] == 'L') {
					accepted_L++;
					art_L += c->customer->responseTime;
					att_L += c->customer->turnaroundTime;
					awt_L += c->customer->waitingTime;
				} else {
					std::cout << "ERROR\n";
				}
			}
		}
	}
	
	printf(
		"*******************************************************************************************\n");
	printf(
		"| Sellers | # Accepted | # Rejected | Average RT | Average TT | Average WT | Throughput |\n");
	printf(
		"*******************************************************************************************\n");
	printf("    H           %d           %d         %.2f         %.2f         %.2f         %.2f \n",
	       accepted_H, n - accepted_H,
	       art_H / accepted_H, att_H / accepted_H, awt_H / accepted_H, (float) accepted_H / time);
	printf("    H           %d           %d         %.2f         %.2f         %.2f         %.2f \n",
	       accepted_M, (3 * n) - accepted_M,
	       art_M / accepted_M, att_M / accepted_M, awt_M / accepted_H, (float) accepted_M / time);
	printf("    H           %d           %d         %.2f         %.2f         %.2f         %.2f \n",
	       accepted_L, (6 * n) - accepted_L,
	       art_L / accepted_L, att_L / accepted_L, awt_L / accepted_L, (float) accepted_L / time);
	printf(
		"*******************************************************************************************\n");
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
