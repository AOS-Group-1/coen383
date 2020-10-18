#ifndef ASSIGNMENT2_RUN_H
#define ASSIGNMENT2_RUN_H

#include "job.h"

int *runAlgorithm(simulation *sim, int quanta,
                  void (*scheduleJobAdd)(process *, int),
                  int (*scheduleJob)(int),
                  void (*clearQueue)());

void calculateData(simulation *sim, const int *run, int quanta);

#endif //ASSIGNMENT2_RUN_H
