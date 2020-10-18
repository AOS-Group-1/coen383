#include "SRT_algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define QUEUELEN 50

process    *SRTqueue[QUEUELEN];
static int SRTstart = 0,
           SRTend   = 0;

int SRTcomp(const void *v1, const void *v2) {
	process *p1 = ((process *) v1);
	process *p2 = ((process *) v2);
	if ((double) p1->remaining_time <= (double) p2->remaining_time) {
		return -1;
	} else if ((double) p1->remaining_time > (double) p2->remaining_time) {
		return 1;
	}
	return 0;
}

static void SRTpush(process *job) {
	SRTqueue[SRTend] = job;
	SRTend = (SRTend + 1) % QUEUELEN;
	if (SRTend > 1) {
		qsort(SRTqueue, SRTend, sizeof(process *), SRTcomp);
	}
}

static process *SRTpop() {
	if (SRTend == 0) return NULL;
	
	process  *ret = SRTqueue[0];
	for (int i    = 0; i < SRTend - 1; i++) {
		SRTqueue[i] = SRTqueue[i + 1];
	}
	SRTend = (SRTend - 1) % QUEUELEN;
	SRTqueue[SRTend] = 0;
	return ret;
}

static process *SRTcurrentJob = NULL;

void SRT_Algorithm_Add(process *job, int quanta) {
	job->remaining_time = job->service_time;
	if (SRTcurrentJob)
		if (SRTcurrentJob->end_time <= (job->remaining_time - 1 + quanta)) {
			SRTpush(job);
		} else {
			process *tempJob = SRTcurrentJob;
			SRTcurrentJob = job;
			SRTcurrentJob->end_time = quanta + fmax(SRTcurrentJob->remaining_time - 1, 0);
			tempJob->remaining_time = tempJob->end_time - quanta + 1;
			SRTpush(tempJob);
		}
	else {
		SRTcurrentJob = job;
		SRTcurrentJob->end_time = quanta + fmax(SRTcurrentJob->remaining_time - 1, 0);
	}
}

int SRT_Algorithm(int quanta) {
	if (SRTcurrentJob && SRTcurrentJob->end_time < quanta) SRTcurrentJob = NULL;
	if (!SRTcurrentJob) {
		SRTcurrentJob = SRTpop();
		if (SRTcurrentJob)
			SRTcurrentJob->end_time = quanta + fmax(SRTcurrentJob->remaining_time - 1, 0);
	}
	if (!SRTcurrentJob) return -1;
	
	return SRTcurrentJob->id;
}

void SRT_clearQueue() {
	SRTend = 0;
}
