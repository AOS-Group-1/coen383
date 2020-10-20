#include <iostream>
#include <algorithm>
#include "customer.h"
#include "seller.h"

bool cmp(Customer *a, Customer *b) {
	return a->arrivalTime < b->arrivalTime;
}

void generate_customers(int n, Seller *seller) {
	std::vector<Customer *> array;
	
	switch (seller->type) {
		case 'H':
			// H-Customers
			for (int i = 1; i <= n; ++i) {
				auto c = new Customer;
				c->id          = seller->type + std::to_string(seller->id);
				c->arrivalTime = rand() % 60;
				c->serviceTime = rand() % 2 + 1;
				array.push_back(c);
			}
			break;
		case 'M':
			// M-Customers
			for (int i = 1; i <= n; ++i) {
				auto c = new Customer;
				c->id          = seller->type + std::to_string(seller->id);
				c->arrivalTime = rand() % 60;
				c->serviceTime = rand() % 3 + 2;
				array.push_back(c);
			}
			break;
		case 'L':
			// L-Customers
			for (int i = 1; i <= n; ++i) {
				auto c = new Customer;
				c->id          = seller->type + std::to_string(seller->id);
				c->arrivalTime = rand() % 60;
				c->serviceTime = rand() % 4 + 4;
				array.push_back(c);
			}
			break;
	}
	std::sort(array.begin(), array.end(), cmp);
	
	int       x = 0;
	for (auto c : array) {
		std::string prefix;
		if (x < 10) prefix = "0";
		c->id += prefix + std::to_string(x++);
		std::cout << c->id << ": " << c->arrivalTime << ", " << c->serviceTime << std::endl;
		seller->eventQueue.push(c);
	}
}

