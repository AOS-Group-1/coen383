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

void Concert::printStats(int n, int time){
    auto seats = this->seats;
    int accepted_H=0, accepted_M=0, accepted_L=0;
    int rejected_H=0, rejected_M=0, rejected_L=0;
    float art_H=0, art_M=0, art_L=0;
    float att_H=0, att_M=0, att_L=0;
    float awt_H=0, awt_M=0, awt_L=0;
    float atp_H=0, atp_M=0, atp_L=0;


    for(int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            if(seats[r][c]->assigned) {
                if (seats[r][c]->customer->seller == "H") {
                    accepted_H++;
                    art_H += seats[r][c]->customer->responseTime;
                    att_H += seats[r][c]->customer->turnaroundTime;
                    awt_H += seats[r][c]->customer->waitingTime;
                } else if (seats[r][c]->customer->seller == "M") {
                    accepted_M++;
                    art_M += seats[r][c]->customer->responseTime;
                    att_M += seats[r][c]->customer->turnaroundTime;
                    awt_M += seats[r][c]->customer->waitingTime;

                } else if (seats[r][c]->customer->seller == "L") {
                    accepted_L++;
                    art_L += seats[r][c]->customer->responseTime;
                    att_L += seats[r][c]->customer->turnaroundTime;
                    awt_L += seats[r][c]->customer->waitingTime;
                } else {
                    std::cout << "ERROR\n";
                }
            }
        }
    }

    printf("*******************************************************************************************\n");
    printf("| Sellers | # Accepted | # Rejected | Average RT | Average TT | Average WT | Throughput |\n");
    printf("*******************************************************************************************\n");
    printf("    H           %d           %d         %.2f         %.2f         %.2f         %.2f \n",
           accepted_H, n-accepted_H, art_H/accepted_H, att_H/accepted_H, awt_H/accepted_H, accepted_H/time);
    printf("    H           %d           %d         %.2f         %.2f         %.2f         %.2f \n",
           accepted_M, (3*n)-accepted_M, art_M/accepted_M, att_M/accepted_M, awt_M/accepted_H, accepted_M/time);
    printf("    H           %d           %d         %.2f         %.2f         %.2f         %.2f \n",
           accepted_L, (6*n)-accepted_L, art_L/accepted_L, att_L/accepted_L, awt_L/accepted_L, accepted_L/time);
    printf("*******************************************************************************************\n");
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
