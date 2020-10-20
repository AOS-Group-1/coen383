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
	float art_H      = 0, art_M = 0, art_L = 0;
	float att_H      = 0, att_M = 0, att_L = 0;
	float awt_H      = 0, awt_M = 0, awt_L = 0;
	
	for (auto &seat : seats) {
		for (auto &s : seat) {
			if (s->assigned) {
				switch (s->customer->id[0]) {
					case 'H':
						accepted_H++;
						art_H += (float) s->customer->responseTime;
						att_H += (float) s->customer->turnaroundTime;
						awt_H += (float) s->customer->waitingTime;
						break;
					case 'M':
						accepted_M++;
						art_M += (float) s->customer->responseTime;
						att_M += (float) s->customer->turnaroundTime;
						awt_M += (float) s->customer->waitingTime;
						break;
					case 'L':
						accepted_L++;
						art_L += (float) s->customer->responseTime;
						att_L += (float) s->customer->turnaroundTime;
						awt_L += (float) s->customer->waitingTime;
						break;
					default:
						std::cout << "ERROR" << std::endl;
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
	       art_H / (float) accepted_H, att_H / (float) accepted_H, awt_H / (float) accepted_H,
	       (float) accepted_H / (float) time);
	printf("    M           %d           %d         %.2f         %.2f         %.2f         %.2f \n",
	       accepted_M, (3 * n) - accepted_M,
	       art_M / (float) accepted_M, att_M / (float) accepted_M, awt_M / (float) accepted_H,
	       (float) accepted_M / (float) time);
	printf("    L           %d           %d         %.2f         %.2f         %.2f         %.2f \n",
	       accepted_L, (6 * n) - accepted_L,
	       art_L / (float) accepted_L, att_L / (float) accepted_L, awt_L / (float) accepted_L,
	       (float) accepted_L / (float) time);
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
