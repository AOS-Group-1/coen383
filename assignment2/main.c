#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "job.h"
#include "run.h"
#include "algorithms/FCFS_algorithm.h"
#include "algorithms/SJF_algorithm.h"
#include "algorithms/SRT_algorithm.h"
#include "algorithms/HPF_P_algorithm.h"

int quanta = 150;

void run(void (*scheduleJobAdd)(process *, int),
         int (*scheduleJob)(int),
         void(*clearQueue)()) {
	double finalResponseTime   = 0,
	       finalWaitingTime    = 0,
	       finalTurnaroundTime = 0;
	int    finalJobs           = 0;
	
	for (int j = 0; j < 5; ++j) {
		simulation *sim = generateJobs(10);
		
		for (int i = 0; i < sim->totalJobs; ++i) {
			process *job = &sim->jobs[i];
			printf("%c: %.1f, %.1f, %i\n", job->id,
			       job->arrival_time, job->service_time, job->priority);
		}
		
		int *run = runAlgorithm(sim, quanta, scheduleJobAdd, scheduleJob, clearQueue);
		
		for (int i = 0; i < quanta; ++i)
			printf("%c", run[i]);
		printf("\n");
		
		calculateData(sim, run, quanta);
		
		double totalResponseTime   = 0,
		       totalWaitingTime    = 0,
		       totalTurnaroundTime = 0;
		
		int    totalJobs = 0;
		double firstTime = 0,
		       finalTime = 0;
		
		for (int i = 0; i < sim->totalJobs; ++i) {
			process *job = &sim->jobs[i];
			if (job->waiting_time != 0) {
				totalJobs++;
				finalJobs++;
				totalResponseTime += job->response_time;
				finalResponseTime += job->response_time;
				totalWaitingTime += job->waiting_time;
				finalWaitingTime += job->waiting_time;
				totalTurnaroundTime += job->turnaround_time;
				finalTurnaroundTime += job->turnaround_time;
				firstTime = fmin(job->arrival_time, firstTime);
				finalTime = fmax(job->arrival_time + job->turnaround_time, finalTime);
			}
		}
		if (totalJobs) {
			printf("average: %.2f, %.2f, %.2f\nthroughput: %.2f\n",
			       totalResponseTime / totalJobs,
			       totalWaitingTime / totalJobs,
			       totalTurnaroundTime / totalJobs,
			       totalJobs / (finalTime - sim->jobs[0].arrival_time));
		}
	}
	printf("final average: %.2f, %.2f, %.2f\n\n",
	       finalResponseTime / finalJobs,
	       finalWaitingTime / finalJobs,
	       finalTurnaroundTime / finalJobs);
}

void runHPF(void (*scheduleJobAdd)(process *, int),
            int (*scheduleJob)(int),
            void (*clearQueue)()) {
	double finalResponseTime[4]   = {0},
	       finalWaitingTime[4]    = {0},
	       finalTurnaroundTime[4] = {0};
	
	int finalJobs[4] = {0};
	
	for (int j = 0; j < 5; ++j) {
		int jobs = 10;
		
		simulation *sim = generateJobs(jobs);
		
		for (int i = 0; i < sim->totalJobs; ++i) {
			process *job = &sim->jobs[i];
			printf("%c: %.1f, %.1f, %i\n", job->id,
			       job->arrival_time, job->service_time, job->priority);
		}
		
		int *run = runAlgorithm(sim, quanta, scheduleJobAdd, scheduleJob, clearQueue);
		
		for (int i = 0; i < quanta; ++i)
			printf("%c", run[i]);
		printf("\n");
		
		calculateData(sim, run, quanta);
		
		double totalResponseTime[4]   = {0},
		       totalWaitingTime[4]    = {0},
		       totalTurnaroundTime[4] = {0};
		
		int    totalJobs[4] = {0};
		double firstTime[4] = {0},
		       finalTime[4] = {0};
		
		for (int i = 0; i < sim->totalJobs; ++i) {
			process *job = &sim->jobs[i];
			if (job->waiting_time != 0) {
				totalJobs[job->priority - 1]++;
				finalJobs[job->priority - 1]++;
				totalResponseTime[job->priority - 1] += job->response_time;
				finalResponseTime[job->priority - 1] += job->response_time;
				totalWaitingTime[job->priority - 1] += job->waiting_time;
				finalWaitingTime[job->priority - 1] += job->waiting_time;
				totalTurnaroundTime[job->priority - 1] += job->turnaround_time;
				finalTurnaroundTime[job->priority - 1] += job->turnaround_time;
				firstTime[job->priority - 1] = fmin(job->arrival_time,
				                                    firstTime[job->priority - 1]);
				finalTime[job->priority - 1] = fmax(job->arrival_time + job->turnaround_time,
				                                    finalTime[job->priority - 1]);
			}
		}
		for (int i = 0; i < 4; ++i) {
			if (totalJobs[i]) {
				printf("priority %i - average: %.2f, %.2f, %.2f\nthroughput: %.2f\n",
				       i + 1,
				       totalResponseTime[i] / totalJobs[i],
				       totalWaitingTime[i] / totalJobs[i],
				       totalTurnaroundTime[i] / totalJobs[i],
				       totalJobs[i] / (finalTime[i] - firstTime[i]));
			}
		}
	}
	for (int i = 0; i < 4; ++i) {
		printf("priority %i - final average: %.2f, %.2f, %.2f\n",
		       i + 1,
		       finalResponseTime[i] / finalJobs[i],
		       finalWaitingTime[i] / finalJobs[i],
		       finalTurnaroundTime[i] / finalJobs[i]);
	}
	printf("\n");
}

int main(int argc, char **argv) {
	int seed = time(NULL);
	if (argc > 1) {
		seed = atoi(argv[1]);
	}
	srand(seed); // guarantee consistency when debugging
	
	printf("FCFS\n");
	run(FCFS_Algorithm_Add, FCFS_Algorithm, FCFS_clearQueue);
	printf("SJF\n");
	run(SJF_Algorithm_Add, SJF_Algorithm, SJF_clearQueue);
	printf("SRT\n");
	run(SRT_Algorithm_Add, SRT_Algorithm, SRT_clearQueue);
//	printf("RR\n");
//	run(RR_Algorithm_Add, RR_Algorithm);
//	printf("HPF (NP)\n");
//	runHPF(HPF_NP_Algorithm_Add, HPF_NP_Algorithm);
	printf("HPF (P)\n");
	runHPF(HPF_P_Algorithm_Add, HPF_P_Algorithm, HPFP_clearQueue);
}
