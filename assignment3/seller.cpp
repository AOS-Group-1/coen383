#include <iostream>
#include "seller.h"

Seller::Seller(char type, int id) {
	this->type = type;
	this->id   = id;
}

std::string printTime(int time) {
	std::string print = std::to_string(time);
	if (print.length() == 1)
		print = "0" + print;
	return print;
}

void Seller::customerArrives(Customer &customer) {
	std::cout << printTime(customer.arrivalTime) << " - " << customer.id << " arrived" << std::endl;
	queue.push(customer);
}

bool Seller::findSeat() {
	switch (this->type) {
		case 'H': {
			int       order[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			for (auto &i : order)
				if (concert.allocateSeat(*this, i)) return true;
			break;
		}
		case 'M': {
			int       order[] = {5, 6, 4, 7, 3, 8, 2, 9, 1, 0};
			for (auto &i : order)
				if (concert.allocateSeat(*this, i)) return true;
			break;
		}
		case 'L': {
			int       order[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
			for (auto &i : order)
				if (concert.allocateSeat(*this, i)) return true;
			break;
		}
	}
	return false;
}

void Seller::timeSlice(int time) {
	if (queue.empty()) return;
	Customer customer = queue.front();
	if (customer.responseTime == 0 && customer.turnaroundTime == 0) {
		std::cout << printTime(time) << " - " << customer.id << " served" << std::endl;
		customer.responseTime = time;
		
		if (findSeat()) {
			customer.turnaroundTime = time + customer.serviceTime;
		} else {
			queue.pop();
		}
	}
	if (time > customer.turnaroundTime) {
		std::cout << printTime(time) << " - " << customer.id << " completed" << std::endl;
		queue.pop();
	}
}
