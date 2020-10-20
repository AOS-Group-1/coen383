#include <iostream>
#include <cmath>
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
	int   min_time_H = 1000, max_time_H = 0;
	int   min_time_M = 1000, max_time_M = 0;
	int   min_time_L = 1000, max_time_L = 0;
	
	for (auto &seat : seats) {
		for (auto &s : seat) {
			if (s->assigned) {
				switch (s->customer->id[0]) {
					case 'H':
						accepted_H++;
						art_H += (float) s->customer->responseTime;
						att_H += (float) s->customer->turnaroundTime;
						min_time_H = (int) fmin(min_time_H, s->customer->arrivalTime);
						max_time_H = (int) fmax(max_time_H, s->customer->arrivalTime +
						                                    s->customer->turnaroundTime);
						break;
					case 'M':
						accepted_M++;
						art_M += (float) s->customer->responseTime;
						att_M += (float) s->customer->turnaroundTime;
						min_time_M = (int) fmin(min_time_M, s->customer->arrivalTime);
						max_time_M = (int) fmax(max_time_M, s->customer->arrivalTime +
						                                    s->customer->turnaroundTime);
						break;
					case 'L':
						accepted_L++;
						art_L += (float) s->customer->responseTime;
						att_L += (float) s->customer->turnaroundTime;
						min_time_L = (int) fmin(min_time_L, s->customer->arrivalTime);
						max_time_L = (int) fmax(max_time_L, s->customer->arrivalTime +
						                                    s->customer->turnaroundTime);
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
		"| Sellers | # Accepted | # Rejected | Average RT | Average TT | Throughput |\n");
	printf(
		"*******************************************************************************************\n");
	printf("    H           %d           %d         %.2f         %.2f         %.2f \n",
	       accepted_H, n - accepted_H,
	       art_H / (float) accepted_H, att_H / (float) accepted_H,
	       (float) accepted_H / (float) (max_time_H - min_time_H));
	printf("    M           %d           %d         %.2f         %.2f         %.2f \n",
	       accepted_M, (3 * n) - accepted_M,
	       art_M / (float) accepted_M, att_M / (float) accepted_M,
	       (float) accepted_M / (float) (max_time_M - min_time_M) / 3);
	printf("    L           %d           %d         %.2f         %.2f         %.2f \n",
	       accepted_L, (6 * n) - accepted_L,
	       art_L / (float) accepted_L, att_L / (float) accepted_L,
	       (float) accepted_L / (float) (max_time_L - min_time_L) / 6);
	printf(
		"*******************************************************************************************\n");
}

bool Concert::allocateSeat(Customer *customer, int row) {
	for (int i = 0; i < 10; i++) {
		if (pthread_mutex_trylock(&locks[row][i]) == 0) {
			/* CRITICAL REGION */
			if (!seats[row][i]->assigned) {
				seats[row][i]->customer = customer;
				seats[row][i]->assigned = true;
				pthread_mutex_unlock(&locks[row][i]);
				printSeats();
				return true;
			}
			/* CRITICAL REGION */
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
