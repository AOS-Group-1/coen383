#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include "customer.h"
#include "seller.h"

using namespace std;

pthread_cond_t  cond        = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex       = PTHREAD_MUTEX_INITIALIZER;
int             currentTime = 0;

#define TIME_LIMIT  60

// seller thread to serve one time slice (1 minute)
void *sell(Seller *seller) {
	// while loops sells ticket while time has not reached TIME_LIMIT (60) minutes
	while (currentTime < TIME_LIMIT * 2) {
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
//		cout << "ID: " << seller->type << seller->id << " | time: " << currentTime << endl;
		
		// Serve any buyer available in this seller queue that is ready
		// now to buy ticket till done with all relevant buyers in their queue
		if (seller->eventQueue.empty() && seller->customerQueue.empty()) {
			pthread_mutex_unlock(&mutex);
			return nullptr;
		}
		
		while (!seller->eventQueue.empty() &&
		       seller->eventQueue.front()->arrivalTime <= currentTime) {
			seller->customerArrives(seller->eventQueue.front(), currentTime);
			seller->eventQueue.pop();
		}
		seller->timeSlice(currentTime);
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
	
	// N : Customers to serve
	int n = 10;
	if (argc > 1) {
		n = stoi(argv[1]);
	}
	
	pthread_t tids[10];
	char      seller_type;
	// Create necessary data structures for the simulator.
	// Create buyers list for each seller ticket queue based on the
	// N value within an hour and have them in the seller queue.
	// Create 10 threads representing the 10 sellers.
	
	seller_type = 'H';
	{
		auto s = new Seller{seller_type, 0};
		generate_customers(n, s);
		pthread_create(&tids[0], nullptr, (void *(*)(void *)) sell, s);
	}
	
	seller_type = 'M';
	for (int i = 1; i < 4; i++) {
		auto s = new Seller{seller_type, i};
		generate_customers(n, s);
		pthread_create(&tids[i], nullptr, (void *(*)(void *)) sell, s);
	}
	
	seller_type = 'L';
	for (int i = 4; i < 10; i++) {
		auto s = new Seller{seller_type, i - 3};
		generate_customers(n, s);
		pthread_create(&tids[i], nullptr, (void *(*)(void *)) sell, s);
	}
	
	usleep(1000);
	// wakeup all seller threads
	for (currentTime = -1; currentTime < TIME_LIMIT * 2; currentTime++) {
		usleep(1000);
		wakeup_all_seller_threads();
	}
	
	// wait for all seller threads to exit
	for (auto &tid : tids)
		pthread_join(tid, nullptr);
	
	// Printout simulation results
	Concert::getInstance()->printSeats();
	Concert::getInstance()->printStats(n, currentTime);
	
	exit(0);
}
