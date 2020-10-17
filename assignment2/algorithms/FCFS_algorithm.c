#include <stdio.h>
#include "FCFS_algorithm.h"

#define QUEUELEN 50

process *FCFSqueue[QUEUELEN];
int     FCFSstart = 0,
        FCFSend   = 0;

void FCFSpush(process *job) {
	FCFSqueue[FCFSend] = job;
	FCFSend = (FCFSend + 1) % QUEUELEN;
}

process *FCFSpop() {
	if (FCFSstart == FCFSend) return NULL;
	
	process *ret = FCFSqueue[FCFSstart];
	FCFSstart = (FCFSstart + 1) % QUEUELEN;
	return ret;
}

void FCFS_Algorithm_Add(process *job, int quanta) {
	job->end_time = job->service_time;
	FCFSpush(job);
}

int FCFS_Algorithm(int quanta) {
	process *currentJob = FCFSqueue[FCFSstart];
	if (currentJob) {
		currentJob->end_time--;
		if (currentJob->end_time <= 0)
			currentJob = FCFSpop();
		if (currentJob)
			return currentJob->id;
	}
	return -1;
}

void FCFS_clearQueue() {
	FCFSstart = 0;
	FCFSend   = 0;
}
