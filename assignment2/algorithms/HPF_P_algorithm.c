#include "HPF_P_algorithm.h"
#include <stdio.h>


#define QUEUELEN 50

process *HPFPqueue1[QUEUELEN];
int     HPFPstart1 = 0,
        HPFPend1   = 0;

process *HPFPqueue2[QUEUELEN];
int     HPFPstart2 = 0,
        HPFPend2   = 0;

process *HPFPqueue3[QUEUELEN];
int     HPFPstart3 = 0,
        HPFPend3   = 0;

process *HPFPqueue4[QUEUELEN];
int     HPFPstart4 = 0,
        HPFPend4   = 0;

void HPFPpush(process **queue, int *start, int *end, process *job) {
	queue[*end] = job;
	*end = (*end + 1) % QUEUELEN;
}

process *HPFPpop(process **queue, int *start, int *end) {
	if (*start == *end) return NULL;
	
	process *ret = queue[*start];
	*start = (*start + 1) % QUEUELEN;
	return ret;
}

void HPF_P_Algorithm_Add(process *job, int quanta) {
}

int HPF_P_Algorithm(int quanta) {
	return -1;
}
