#include "SJF_algorithm.h"
#include "priority_queue.h"
#include <stdio.h>
#include <math.h>

void SJF_Algorithm_Add(process *job, int quanta) {
    if (currJob)
        insert(job);
    else {
        currJob = job;
        currJob->end_time = quanta + fmax(currJob->service_time - 1, 0);
    }
}

int SJF_Algorithm(int quanta) {
	if (currJob && currJob->end_time < quanta) currJob = NULL;
    if (!currJob) {
        currJob = removeData();
        if (currJob) currJob->end_time = quanta + fmax(currJob->service_time - 1, 0);
    }
    if (!currJob) return -1;
    
    return currJob->id;
}
