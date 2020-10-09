#include <stdlib.h>
#include "run.h"

int *runAlgorithm(simulation *sim, int quanta, int (*scheduleJob)(simulation *, int, process *)) {
	int *run       = malloc(sizeof(int) * (quanta));
	int currentJob = 0;
	
	for (int time = 0; time < quanta; ++time) {
		process *job = sim->jobs[currentJob];
		if (currentJob < sim->totalJobs && job->arrival_time <= time) {
			while ((currentJob < sim->totalJobs && job->arrival_time <= time)) {
				run[time] = scheduleJob(sim, time, job);
				job = sim->jobs[++currentJob];
			}
		} else {
			run[time] = scheduleJob(sim, time, NULL);
		}
		if (run[time] == -1) run[time] = '-';
	}
	
	return run;
}

void calculateData(simulation *sim, const int *run, int quanta) {
	for (int i = 0; i < quanta; ++i) {
		process *job = sim->jobs[run[i]];
		if (run[i] != '-') {
			if (!job->response_time) {
				job->response_time   = i;
				job->turnaround_time = i + job->service_time;
			} else {
				job->turnaround_time = i;
			}
		}
	}
	for (int i = 0; i < sim->totalJobs; ++i) {
		process *job      = sim->jobs[i];
		job->waiting_time = job->response_time - job->turnaround_time;
		job->turnaround_time -= job->arrival_time;
		job->response_time -= job->arrival_time;
	}
}
