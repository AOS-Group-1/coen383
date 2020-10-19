#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
#include "customer.h"
#include "seller.h"
#include "unistd.h"

using namespace std;

pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int current_time = 0;
int run = 0;
int TIME_LIMIT = 60;
int TOTAL_SEATS = 100;

// seller thread to serve one time slice (1 minute)
void *sell(Seller *seller_info) {

    //pthread_mutex_lock(&mutex);
    //pthread_cond_wait(&cond, &mutex);
    //pthread_mutex_unlock(&mutex);


	// while loops sells ticket while
	// 1. time has not reached TIME_LIMIT (60) minutes
	// 2. seats sold is not more than TOTAL_SEATS (100) seats
	while (current_time < TIME_LIMIT /* && seats_sold < TOTAL_SEATS */) {

        pthread_mutex_lock(&mutex);
        printf("P: %p | Type: %c | ID: %d | time: %d | run: %d\n", &seller_info, seller_info->type, seller_info->id, current_time, run);
        run++;

        if(run % 10 == 0){
            current_time++;
            pthread_cond_broadcast(&cond);
        }

        while(run < 10){
            //cout << "WAITING ID : " << seller_info->id << " | CT: " << current_time << "| RUNS: " << run << endl;
            pthread_cond_wait(&cond, &mutex);
        }

        //run = 0;
        pthread_mutex_unlock(&mutex);



		// TODO: Serve any buyer available in this seller queue that is ready
		// now to buy ticket till done with all relevant buyers in their queue

		// HIGH SELLER
		if(seller_info->type == 'H') {
			// if buyer in high seller queue
			if(!seller_info->queue.empty()) {
				// sell ticket to buyer in high queue


				// update current_time (generate random time [1,2] minutes)
				current_time = current_time + (rand() % 2) + 1;
			}
		}
		// MEDIUM SELLER
		else if(seller_info->type == 'M') {
			if(!seller_info->queue.empty()) {
				// sell ticket to buyer in medium queues


				// update current_time (generate random time [2,4] minutes)
				current_time = current_time + (rand() % 3) + 2;
			}
		}
		// LOW SELLER
		else {
			// if buyer in low seller queue
			if(!seller_info->queue.empty()) {
				// sell ticket to buyer in low queues
			
			
				// update current_time (generate random time [4,7] minutes)
				current_time = current_time + (rand() % 4) + 4;
			}
		}

	}

	return NULL; // thread exits
}

void wakeup_all_seller_threads() {
	pthread_mutex_lock(&mutex);
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv) {

    int seed = time(NULL);
    srand(seed);
    srand(0);

    // N : Customers to server
    int n = 10;
    if(argc > 1){
        n = atoi(argv[1]);
    }



	pthread_t tids[10];
	char      seller_type;
	// Create necessary data structures for the simulator.
	// Create buyers list for each seller ticket queue based on the
	// N value within an hour and have them in the seller queue.
	// Create 10 threads representing the 10 sellers.

	seller_type = 'H';
    Seller *s = new Seller {seller_type, 0};
    generate_customers(n, s->queue, seller_type);

	pthread_create(&tids[0], NULL, (void *(*)(void *)) sell, s);

	seller_type = 'M';
	for (int i = 1; i < 4; i++){
        Seller *s = new Seller {seller_type, i};
        generate_customers(n, s->queue, seller_type);
        pthread_create(&tids[i], NULL, (void *(*)(void *)) sell, s);
	}

	seller_type = 'L';
	for (int i = 4; i < 10; i++) {
        Seller *s = new Seller {seller_type, i};
        generate_customers(n, s->queue, seller_type);
        pthread_create(&tids[i], NULL, (void *(*)(void *)) sell, s);
    }
	
	// wakeup all seller threads
	wakeup_all_seller_threads();
	// wait for all seller threads to exit
	for (int i = 0; i < 10; i++)
		pthread_join(tids[i], NULL);

	// TODO: Printout simulation results
	exit(0);
}
