#include <time.h>
#include <stdio.h>
#include "job.h"
#include "run.h"
#include "algorithm.h"

int main() {
	int seed = time(NULL);
//	srand(seed); // guarantee consistency when debugging
	
	int totalJobs = 20;
	
	simulation *sim = generateJobs(totalJobs);
	
	for (int i = 0; i < sim->totalJobs; ++i) {
		process *job = sim->jobs[i];
//		printf("%.1f, %.1f, %i\n", job->arrival_time, job->service_time, job->priority);
		printf("%0*d%*c%0*d\n", (int) job->arrival_time, 0,
		       (int) job->service_time, ' ',
		       (int) (110 - job->arrival_time - job->service_time), 0);
	}
	
	int quanta = 200;
	int *run   = runAlgorithm(sim, quanta, FCFS_Algorithm);
	
	for (int i = 0; i < quanta; ++i)
		printf("%c", run[i]);
	printf("\n");
	
	calculateData(sim, run, quanta);
	
	for (int i = 0; i < sim->totalJobs; ++i)
		printf("%.1f, %.1f, %.1f\n", sim->jobs[i]->turnaround_time, sim->jobs[i]->waiting_time,
		       sim->jobs[i]->response_time);
	
}
