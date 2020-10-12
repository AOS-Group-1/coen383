#include "SRT_algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define QUEUELEN 50

process *queue[QUEUELEN];
static int     start = 0,
        end   = 0;

int comp(const void * v1, const void * v2) {
	process *p1 = ((process *) v1);
	process *p2 = ((process *) v2);
	if((double) p1->service_time <= (double) p2->service_time) {
		return -1;
	}
	else if((double) p1->service_time > (double) p2->service_time) {
		return 1;
	}
	return 0;
}

static void push(process *job, int quanta) {
	queue[end] = job;
	end = (end + 1) % QUEUELEN;
	if(end > 1) {
		qsort(queue, end, sizeof(process *), comp);
	}
}

static process *pop(int quanta) {
	if (end == 0) return NULL;
	
	process *ret = queue[0];
	for(int i = 0; i < end-1; i++) {
		queue[i] = queue[i+1];
	}
	end = (end - 1) % QUEUELEN;
	queue[end] = 0;
	return ret;
}

static process *currentJob = NULL;

void SRT_Algorithm_Add(process *job, int quanta) {
	if (currentJob)
		if(currentJob->end_time <= (job->service_time - 1 + quanta)) {
			push(job, quanta);		
		}
		else {
			process *tempJob = currentJob;
			currentJob = job;
			currentJob->end_time = quanta + fmax(currentJob->service_time - 1, 0);
			tempJob->service_time = tempJob->end_time - quanta;
			tempJob->end_time = 0;
			push(tempJob, quanta);
		}
	else {
		currentJob = job;
		currentJob->end_time = quanta + fmax(currentJob->service_time - 1, 0);
	}
}

int SRT_Algorithm(int quanta) {
	if (currentJob && currentJob->end_time < quanta) currentJob = NULL;
	if (!currentJob) {
		currentJob = pop(quanta);
		if (currentJob) currentJob->end_time = quanta + fmax(currentJob->service_time - 1, 0);
	}
	if (!currentJob) return -1;
	
	return currentJob->id;
}
