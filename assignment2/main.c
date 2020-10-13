#include <time.h>
#include <stdio.h>
#include "job.h"
#include "run.h"
#include "algorithms/FCFS_algorithm.h"
#include "algorithms/SJF_algorithm.h"
#include "algorithms/SRT_algorithm.h"
#include "algorithms/RR_algorithm.h"
#include "algorithms/HPF_NP_algorithm.h"
#include "algorithms/HPF_P_algorithm.h"

int quanta = 110;

void run(simulation *sim,
         void (*scheduleJobAdd)(process *, int),
         int (*scheduleJob)(int)) {
	resetJobStats(sim);
	
	int *run = runAlgorithm(sim, quanta, scheduleJobAdd, scheduleJob);
	
	for (int i = 0; i < quanta; ++i)
		printf("%c", run[i]);
	printf("\n");
	
	calculateData(sim, run, quanta);
	
	double totalResponseTime   = 0,
	       totalWaitingTime    = 0,
	       totalTurnaroundTime = 0;
	
	int    totalJobs = 0;
	double finalTime = 0;
	
	for (int i = 0; i < sim->totalJobs; ++i) {
		process *job = sim->jobs[i];
		if (job->waiting_time != 0) {
			totalJobs++;
			printf("%c: %.1f, %.1f, %.1f\n",
			       job->id,
			       job->response_time,
			       job->waiting_time,
			       job->turnaround_time);
			totalResponseTime += job->response_time;
			totalWaitingTime += job->waiting_time;
			totalTurnaroundTime += job->turnaround_time;
			finalTime = job->arrival_time + job->turnaround_time;
		}
	}
	if (totalJobs) {
		printf("average: %.1f, %.1f, %.1f\nthroughput: %.1f\n",
		       totalResponseTime / totalJobs,
		       totalWaitingTime / totalJobs,
		       totalTurnaroundTime / totalJobs,
		       (finalTime - sim->jobs[0]->arrival_time) / totalJobs);
	}
}

int main() {
	int seed = time(NULL);
//	srand(seed); // guarantee consistency when debugging
	
	int totalJobs = 10;
	
	simulation *sim = generateJobs(totalJobs);
	
	for (int i = 0; i < sim->totalJobs; ++i) {
		process *job = sim->jobs[i];
		printf("%c: %.1f, %.1f, %i\n", job->id,
		       job->arrival_time, job->service_time, job->priority);
		/*printf("%0*d%*c%0*d\n", (int) job->arrival_time, 0,
		       (int) job->service_time, ' ',
		       (int) (quanta - job->arrival_time - job->service_time), 0);*/
	}
	
	printf("FCFS\n");
	run(sim, FCFS_Algorithm_Add, FCFS_Algorithm);
	printf("SJF\n");
	run(sim, SJF_Algorithm_Add, SJF_Algorithm);
	printf("SRT\n");
	run(sim, SRT_Algorithm_Add, SRT_Algorithm);
	printf("RR\n");
	run(sim, RR_Algorithm_Add, RR_Algorithm);
	printf("HPF (NP)\n");
	run(sim, HPF_NP_Algorithm_Add, HPF_NP_Algorithm);
	printf("HPF (P)\n");
	run(sim, HPF_P_Algorithm_Add, HPF_P_Algorithm);
}
