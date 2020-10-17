#include "SJF_algorithm.h"
#include "priority_queue.h"
#include <stdio.h>
#include <math.h>

process *SJFcurrJob;

void SJF_Algorithm_Add(process *job, int quanta) {
    if (SJFcurrJob)
        insert(job);
    else {
	    SJFcurrJob = job;
	    SJFcurrJob->end_time = quanta + fmax(SJFcurrJob->service_time - 1, 0);
    }
}

int SJF_Algorithm(int quanta) {
	if (SJFcurrJob && SJFcurrJob->end_time < quanta) SJFcurrJob = NULL;
    if (!SJFcurrJob) {
	    SJFcurrJob = removeData();
        if (SJFcurrJob) SJFcurrJob->end_time = quanta + fmax(SJFcurrJob->service_time - 1, 0);
    }
    if (!SJFcurrJob) return -1;
    
    return SJFcurrJob->id;
}

void SJF_clearQueue() {
}
