#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
#include "customer.h"
#include "seller.h"
#include "unistd.h"

using namespace std;

pthread_cond_t  cond         = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex        = PTHREAD_MUTEX_INITIALIZER;
int             current_time = 0;
int             run          = 0;
int             TIME_LIMIT   = 10;
int             TOTAL_SEATS  = 100;

// seller thread to serve one time slice (1 minute)
void *sell(Seller *seller_info) {
	
	//pthread_mutex_lock(&mutex);
	//pthread_cond_wait(&cond, &mutex);
	//pthread_mutex_unlock(&mutex);
	
	
	// while loops sells ticket while
	// 1. time has not reached TIME_LIMIT (60) minutes
	// 2. seats sold is not more than TOTAL_SEATS (100) seats
	while (current_time < TIME_LIMIT) {
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
		cout << "ID: " << seller_info->type << seller_info->id << " | time: " << current_time
		     << endl;
		
		// TODO: Serve any buyer available in this seller queue that is ready
		// now to buy ticket till done with all relevant buyers in their queue
		
		if (seller_info->eventQueue.front().arrivalTime >= current_time) {
			seller_info->customerArrives(seller_info->eventQueue.front());
			seller_info->eventQueue.pop();
		}
		seller_info->timeSlice(current_time);
		pthread_mutex_unlock(&mutex);
	}
	
	return nullptr; // thread exits
}

void wakeup_all_seller_threads() {
	pthread_mutex_lock(&mutex);
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv) {
	
	int seed = time(nullptr);
	srand(seed);
	
	// N : Customers to server
	int n = 10;
	if (argc > 1) {
		n = atoi(argv[1]);
	}
	
	
	pthread_t tids[10];
	char      seller_type;
	// Create necessary data structures for the simulator.
	// Create buyers list for each seller ticket queue based on the
	// N value within an hour and have them in the seller queue.
	// Create 10 threads representing the 10 sellers.
	
	seller_type = 'H';
	auto s = new Seller{seller_type, 0};
	generate_customers(n, s->eventQueue, seller_type);
	pthread_create(&tids[0], nullptr, (void *(*)(void *)) sell, s);
	
	seller_type = 'M';
	for (int i = 1; i < 4; i++) {
		auto s = new Seller{seller_type, i};
		generate_customers(n, s->eventQueue, seller_type);
		pthread_create(&tids[i], nullptr, (void *(*)(void *)) sell, s);
	}
	
	seller_type = 'L';
	for (int i = 4; i < 10; i++) {
		auto s = new Seller{seller_type, i};
		generate_customers(n, s->eventQueue, seller_type);
		pthread_create(&tids[i], nullptr, (void *(*)(void *)) sell, s);
	}
	usleep(10000);
	// wakeup all seller threads
	for (current_time = 0; current_time < TIME_LIMIT; current_time++) {
		usleep(10000);
		wakeup_all_seller_threads();
	}
	
	// wait for all seller threads to exit
	for (auto &tid : tids)
		pthread_join(tid, nullptr);
	
	// TODO: Printout simulation results
	exit(0);
}
