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
	return "0:" + print;
}

void Seller::customerArrives(Customer *customer, int time) {
	std::cout << printTime(time) << " - " << customer->id << " arrived" << std::endl;
	customerQueue.push(customer);
}

bool Seller::findSeat(Customer *customer) const {
	switch (type) {
		case 'H': {
			int       order[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			for (auto &i : order)
				if (Concert::getInstance()->allocateSeat(customer, i)) return true;
			break;
		}
		case 'M': {
			int       order[] = {5, 6, 4, 7, 3, 8, 2, 9, 1, 0};
			for (auto &i : order)
				if (Concert::getInstance()->allocateSeat(customer, i)) return true;
			break;
		}
		case 'L': {
			int       order[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
			for (auto &i : order)
				if (Concert::getInstance()->allocateSeat(customer, i)) return true;
			break;
		}
	}
	return false;
}

void Seller::timeSlice(int time) {
	if (customerQueue.empty()) return;
	Customer *customer = customerQueue.front();
	if (customer->responseTime == -1 && customer->turnaroundTime == -1) {
		customer->responseTime = time;
		if (time < 60 && findSeat(customer)) {
			std::cout << printTime(time) << " - " << customer->id << " served" << std::endl;
			customer->turnaroundTime = time + customer->serviceTime - 1;
		} else {
			std::cout << printTime(time) << " - " << customer->id << " rejected" << std::endl;
			customer->responseTime -= customer->arrivalTime;
			customer->turnaroundTime = 0;
			customerQueue.pop();
			return;
		}
	}
	if (time >= customer->turnaroundTime) {
		std::cout << printTime(time) << " - " << customer->id << " completed" << std::endl;
		customer->responseTime -= customer->arrivalTime;
		customer->turnaroundTime = time - customer->arrivalTime;
		customerQueue.pop();
	}
}
