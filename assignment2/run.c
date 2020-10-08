#include <stdlib.h>
#include "run.h"

int *runAlgorithm(struct Process **queue, int totalJobs, int quanta, int (*scheduleJob)(int, struct Process *)) {
	int *run       = malloc(sizeof(int) * (quanta + 50));
	int currentJob = 0;
	
	for (int time = 0; time < quanta + 50; ++time) {
		if (currentJob < totalJobs && queue[currentJob]->arrival_time < time) {
			while ((currentJob < totalJobs && queue[currentJob]->arrival_time < time)) {
				run[time] = scheduleJob(time, queue[currentJob]);
				currentJob++;
			}
		} else {
			run[time] = scheduleJob(time, NULL);
		}
		if (run[time] == -1) run[time] = '-';
	}
	
	return run;
}

void calculateData(struct Process **jobs, int totalJobs, const int *run, int quanta) {
	for (int i = 0; i < quanta; ++i) {
		if (run[i] != '-') {
			if (!jobs[run[i]]->response_time) {
				jobs[run[i]]->response_time   = i;
				jobs[run[i]]->turnaround_time = i + jobs[run[i]]->service_time;
			} else {
				jobs[run[i]]->turnaround_time = i;
			}
		}
	}
	for (int i = 0; i < totalJobs; ++i) {
		jobs[i]->waiting_time = jobs[i]->response_time - jobs[i]->turnaround_time;
		jobs[i]->turnaround_time -= jobs[i]->arrival_time;
		jobs[i]->response_time -= jobs[i]->arrival_time;
	}
}
