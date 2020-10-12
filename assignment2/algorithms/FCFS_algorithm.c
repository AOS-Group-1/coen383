#include "FCFS_algorithm.h"
#include <stdio.h>
#include <math.h>

#define QUEUELEN 50

process *FCFSqueue[QUEUELEN];
int     SRTstart = 0,
        SRTend   = 0;

void FCFSpush(process *job) {
	FCFSqueue[SRTend] = job;
	SRTend = (SRTend + 1) % QUEUELEN;
}

process *FCFSpop() {
	if (SRTstart == SRTend) return NULL;
	
	process *ret = FCFSqueue[SRTstart];
	SRTstart = (SRTstart + 1) % QUEUELEN;
	return ret;
}

process *FCFScurrentJob = NULL;

void FCFS_Algorithm_Add(process *job, int quanta) {
	if (FCFScurrentJob)
		FCFSpush(job);
	else {
		FCFScurrentJob = job;
		FCFScurrentJob->end_time = quanta + fmax(FCFScurrentJob->service_time - 1, 0);
	}
}

int FCFS_Algorithm(int quanta) {
	if (FCFScurrentJob && FCFScurrentJob->end_time < quanta) FCFScurrentJob = NULL;
	if (!FCFScurrentJob) {
		FCFScurrentJob = FCFSpop();
		if (FCFScurrentJob) FCFScurrentJob->end_time = quanta + fmax(FCFScurrentJob->service_time - 1, 0);
	}
	if (!FCFScurrentJob) return -1;
	
	return FCFScurrentJob->id;
}
