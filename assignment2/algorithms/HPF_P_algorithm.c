#include "HPF_P_algorithm.h"
#include <stdio.h>
#include <math.h>

#define QUEUELEN 50

// 4 Priority Queues (1 = LOW, 4 = HIGH)
process *queue1[QUEUELEN];
process *queue2[QUEUELEN];
process *queue3[QUEUELEN];
process *queue4[QUEUELEN];

int start[4] = {0}, 
	end[4] = {0};

void push(process *job) {
	switch(job->priority) {
		case 1:
			queue1[end[0]] = job;
			end[0] = (end[0] + 1) % QUEUELEN;
			break;
		case 2:
			queue2[end[1]] = job;
			end[1] = (end[1] + 1) % QUEUELEN;
			break;
		case 3:
			queue3[end[2]] = job;
			end[2] = (end[2] + 1) % QUEUELEN;
			break;
		case 4:
			queue4[end[3]] = job;
			end[3] = (end[3] + 1) % QUEUELEN;
			break;
	}
}

process *pop(int priority) {
	if(start[priority] == end[priority]) return NULL;

	process *ret = NULL;

	switch(priority) {
		case 1:
			ret = queue1[start[0]];
			start[0] = start[0] + 1 % QUEUELEN;
			break;
		case 2:
			ret = queue2[start[1]];
			start[1] = start[1] + 1 % QUEUELEN;
			break;
		case 3:
			ret = queue3[start[2]];
			start[2] = start[2] + 1 % QUEUELEN;
			break;	
		case 4:
			ret = queue4[start[3]];
			start[3] = start[3] + 1 % QUEUELEN;
			break;
	}

	return ret;
}

process *currentJob = NULL;

void HPF_P_Algorithm_Add(process *job, int quanta) {
	if(currentJob)
		push(job);
	else {
		currentJob = job;
		currentJob->end_time = quanta + fmax(currentJob->service_time - 1, 0);
	}
}

int HPF_P_Algorithm(int quanta) {
	return -1;
}
