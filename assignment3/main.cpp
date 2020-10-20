#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <pthread.h>
#include <iostream>
#include "customer.h"
#include "seller.h"
#include "unistd.h"
#include <algorithm>

using namespace std;

pthread_cond_t  cond        = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex       = PTHREAD_MUTEX_INITIALIZER;
int             currentTime = 0;

#define TIME_LIMIT  60
#define TOTAL_SEATS 100

// seller thread to serve one time slice (1 minute)
void *sell(Seller *seller_info) {
	
	// while loops sells ticket while time has not reached TIME_LIMIT (60) minutes
	while (currentTime < TIME_LIMIT) {
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
//		cout << "ID: " << seller_info->type << seller_info->id << " | time: " << currentTime
//		     << endl;
		
		// TODO: Serve any buyer available in this seller queue that is ready
		// now to buy ticket till done with all relevant buyers in their queue
		
		if (seller_info->eventQueue.front()->arrivalTime <= currentTime) {
			seller_info->customerArrives(seller_info->eventQueue.front());
			seller_info->eventQueue.pop();
		}
		seller_info->timeSlice(currentTime - 1);
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
	generate_customers(n, s, seller_type);
	pthread_create(&tids[0], nullptr, (void *(*)(void *)) sell, s);
	
	seller_type = 'M';
	for (int i = 1; i < 4; i++) {
		auto s = new Seller{seller_type, i};
		generate_customers(n, s, seller_type);
		pthread_create(&tids[i], nullptr, (void *(*)(void *)) sell, s);
	}
	
	seller_type = 'L';
	for (int i = 4; i < 10; i++) {
		auto s = new Seller{seller_type, i};
		generate_customers(n, s, seller_type);
		pthread_create(&tids[i], nullptr, (void *(*)(void *)) sell, s);
	}
	usleep(10000);
	// wakeup all seller threads
	for (currentTime = 0; currentTime < TIME_LIMIT; currentTime++) {
		usleep(10000);
		wakeup_all_seller_threads();
	}
	
	// wait for all seller threads to exit
	for (auto &tid : tids)
		pthread_join(tid, nullptr);
	
	// TODO: Printout simulation results
	exit(0);
}
