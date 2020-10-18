#include <stdio.h>
#include "HPF_P_algorithm.h"

#define QUEUELEN 50

process HPFPqueue[4][50];
int     HPFPstart[4] = {0},
        HPFPend[4]   = {0};

void HPFPpush(process *queue, int *start, int *end, process *job) {
	queue[*end] = *job;
	*end = (*end + 1) % QUEUELEN;
}

process *HPFPpop(process *queue, int *start, int *end) {
	if (*start == *end) return NULL;
	
	process *ret = &queue[*start];
	*start = (*start + 1) % QUEUELEN;
	return ret;
}

void HPF_P_Algorithm_Add(process *job, int quanta) {
	job->end_time       = job->service_time;
	job->remaining_time = 6;
	HPFPpush(HPFPqueue[job->priority - 1],
	         &HPFPstart[job->priority - 1],
	         &HPFPend[job->priority - 1],
	         job);
}

int HPF_P_Algorithm(int quanta) {
	for (int i = 1; i < 4; ++i) {
		for (int j = HPFPstart[i]; j != HPFPend[i]; j = (j + 1) % QUEUELEN) {
			process *currentJob = &(HPFPqueue[i][j]);
			currentJob->remaining_time--;
		}
		while (HPFPstart[i] != HPFPend[i]) {
			process *currentJob = &(HPFPqueue[i][HPFPstart[i]]);
			if (currentJob && currentJob->remaining_time <= 0) {
				currentJob = HPFPpop(HPFPqueue[i], &HPFPstart[i], &HPFPend[i]);
				currentJob->remaining_time = 6;
				HPFPpush(HPFPqueue[i - 1], &HPFPstart[i - 1], &HPFPend[i - 1], currentJob);
			} else
				break;
		}
	}
	for (int i = 0; i < 4; ++i) {
		process *currentJob = HPFPpop(HPFPqueue[i], &HPFPstart[i], &HPFPend[i]);
		if (currentJob) {
			currentJob->end_time--;
			if (currentJob->end_time > 0) {
				HPFPpush(HPFPqueue[i], &HPFPstart[i], &HPFPend[i], currentJob);
			}
			return currentJob->id;
		}
	}
	return -1;
}

void HPFP_clearQueue() {
	for (int i = 0; i < 4; ++i) {
		HPFPstart[i] = 0;
		HPFPend[i]   = 0;
	}
}
