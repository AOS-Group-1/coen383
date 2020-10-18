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

void Seller::timeSlice(int time) {
	if (queue.empty()) return;
	Customer customer = queue.front();
	if (customer.responseTime == 0) {
		std::cout << printTime(time) << " - " << customer.id << " served" << std::endl;
		customer.responseTime   = time;
		customer.turnaroundTime = time + customer.serviceTime;
	}
	if (time > customer.turnaroundTime) {
		std::cout << printTime(time) << " - " << customer.id << " completed" << std::endl;
		queue.pop();
	}
}
