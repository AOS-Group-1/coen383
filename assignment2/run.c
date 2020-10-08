#include <stdlib.h>
#include "run.h"

int *runAlgorithm(simulation *queue, int quanta, int (*scheduleJob)(int, process *)) {
	int *run       = malloc(sizeof(int) * (quanta));
	int currentJob = 0;
	
	for (int time = 0; time < quanta; ++time) {
		process *job = queue->jobs[currentJob];
		if (currentJob < queue->totalJobs && job->arrival_time < time) {
			while ((currentJob < queue->totalJobs && job->arrival_time < time)) {
				run[time] = scheduleJob(time, job);
				job = queue->jobs[++currentJob];
			}
		} else {
			run[time] = scheduleJob(time, NULL);
		}
		if (run[time] == -1) run[time] = '-';
	}
	
	return run;
}

void calculateData(simulation *queue, const int *run, int quanta) {
	for (int i = 0; i < quanta; ++i) {
		process *job = queue->jobs[run[i]];
		if (run[i] != '-') {
			if (!job->response_time) {
				job->response_time   = i;
				job->turnaround_time = i + job->service_time;
			} else {
				job->turnaround_time = i;
			}
		}
	}
	for (int i = 0; i < queue->totalJobs; ++i) {
		process *job      = queue->jobs[i];
		job->waiting_time = job->response_time - job->turnaround_time;
		job->turnaround_time -= job->arrival_time;
		job->response_time -= job->arrival_time;
	}
}
