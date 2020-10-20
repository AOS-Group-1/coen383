#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "customer.h"
#include "seller.h"

bool cmp(Customer *a, Customer *b) {
	return a->arrivalTime < b->arrivalTime;
}

void generate_customers(int n, Seller *seller) {
	std::vector<Customer *> array;
	
	// H-Customers
	if (seller->type == 'H')
		for (int i = 0; i < n; ++i) {
			auto c = new Customer();
			c->id          = seller->type + std::to_string(seller->id);
			c->arrivalTime = rand() % 60;
			c->serviceTime = rand() % 2 + 1;
			array.push_back(c);
		}
	// M-Customers
	if (seller->type == 'M')
		for (int i = 0; i < n; ++i) {
			auto c         = new Customer();
			c->id          = seller->type + std::to_string(seller->id);
			c->arrivalTime = rand() % 60;
			c->serviceTime = rand() % 3 + 2;
			array.push_back(c);
		}
	
	// L-Customers
	if (seller->type == 'L')
		for (int i = 0; i < n; ++i) {
			auto c = new Customer();
			c->id          = seller->type + std::to_string(seller->id);
			c->arrivalTime = rand() % 60;
			c->serviceTime = rand() % 4 + 4;
			array.push_back(c);
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

