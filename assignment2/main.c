#include <time.h>
#include <stdio.h>
#include "job.h"
#include "run.h"
#include "algorithm.h"

int main() {
	int seed = time(NULL);
//	srand(seed); // guarantee consistency when debugging
	
	int totalJobs = 10;
	
	struct Process **queue = generateJobs(totalJobs);
	
	for (int i = 0; i < totalJobs; ++i)
		printf("%.1f, %.1f, %i\n", queue[i]->arrival_time, queue[i]->service_time, queue[i]->priority);
	
	int quanta = 150;
	int *run   = runAlgorithm(queue, totalJobs, quanta, basicAlgorithm);
	
	for (int i = 0; i < quanta; ++i)
		printf("%c", run[i]);
	printf("\n");

//	calculateData(queue, totalJobs, run, quanta);
//
//	for (int i = 0; i < totalJobs; ++i)
//		printf("%.1f, %.1f, %.1f\n", queue[i]->turnaround_time, queue[i]->waiting_time, queue[i]->response_time);
	
}
