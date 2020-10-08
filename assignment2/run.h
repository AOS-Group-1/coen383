#ifndef ASSIGNMENT2_RUN_H
#define ASSIGNMENT2_RUN_H

#include "job.h"

int *runAlgorithm(simulation *queue, int quanta, int (*scheduleJob)(int, process *));

void calculateData(simulation *queue, const int *run, int quanta);

#endif //ASSIGNMENT2_RUN_H
