#ifndef ASSIGNMENT2_RUN_H
#define ASSIGNMENT2_RUN_H

#include "job.h"

int *runAlgorithm(struct Process **queue, int totalJobs, int quanta, int (*scheduleJob)(int, struct Process *));

void calculateData(struct Process **jobs, int totalJobs, const int *run, int quanta);

#endif //ASSIGNMENT2_RUN_H
