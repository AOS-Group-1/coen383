#include <time.h>
#include <stdio.h>
#include "job.h"
#include "run.h"
#include "algorithm.h"

int main() {
	int seed = time(NULL);
//	srand(seed); // guarantee consistency when debugging
	
	int totalJobs = 20;
	
	simulation *queue = generateJobs(totalJobs);
	
	for (int i = 0; i < queue->totalJobs; ++i) {
		process *job = queue->jobs[i];
//		printf("%.1f, %.1f, %i\n", job->arrival_time, job->service_time, job->priority);
		printf("%0*d%*c%0*d\n", (int) job->arrival_time, 0,
		       (int) job->service_time, ' ',
		       (int) (110 - job->arrival_time - job->service_time), 0);
	}
	
	int quanta = 150;
	int *run   = runAlgorithm(queue, quanta, basicAlgorithm);
	
	for (int i = 0; i < quanta; ++i)
		printf("%c", run[i]);
	printf("\n");
	
	calculateData(queue, run, quanta);
	
	for (int i = 0; i < queue->totalJobs; ++i)
		printf("%.1f, %.1f, %.1f\n", queue->jobs[i]->turnaround_time, queue->jobs[i]->waiting_time,
		       queue->jobs[i]->response_time);
	
}
