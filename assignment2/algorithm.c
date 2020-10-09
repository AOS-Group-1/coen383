#include "algorithm.h"
#include <stdio.h>

#define QUEUELEN 50

process *queue[QUEUELEN];
int     start = 0,
        end   = 0;

void push(process *job) {
	queue[end] = job;
	end = (end + 1) % QUEUELEN;
}

process *pop() {
	if (start == end) return NULL;
	
	process *ret = queue[start];
	start = (start + 1) % QUEUELEN;
	return ret;
}

process *currentJob = NULL;
double  currentJobEnd;

void FCFS_Algorithm_Add(simulation *sim, process *job, int quanta) {
	if (currentJob)
		push(job);
	else {
		currentJob    = job;
		currentJobEnd = quanta + currentJob->service_time;
	}
}

int FCFS_Algorithm(simulation *sim, int quanta) {
	if (currentJob && currentJobEnd < quanta) currentJob = NULL;
	if (!currentJob) {
		currentJob = pop();
		if (currentJob) currentJobEnd = quanta + currentJob->service_time - 1;
	}
	if (!currentJob) return -1;
	
	return currentJob->id;
}
