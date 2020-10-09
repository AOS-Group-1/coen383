#include "FCFS_algorithm.h"
#include <stdio.h>
#include <math.h>

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

void FCFS_Algorithm_Add(process *job, int quanta) {
	if (currentJob)
		push(job);
	else {
		currentJob = job;
		currentJob->end_time = quanta + fmax(currentJob->service_time - 1, 0);
	}
}

int FCFS_Algorithm(int quanta) {
	if (currentJob && currentJob->end_time < quanta) currentJob = NULL;
	if (!currentJob) {
		currentJob = pop();
		if (currentJob) currentJob->end_time = quanta + currentJob->service_time - 1;
	}
	if (!currentJob) return -1;
	
	return currentJob->id;
}
