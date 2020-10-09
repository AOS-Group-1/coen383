#ifndef ASSIGNMENT2_RUN_H
#define ASSIGNMENT2_RUN_H

#include "job.h"

int *runAlgorithm(simulation *sim, int quanta,
                  void (*scheduleJobAdd)(simulation *, process *, int),
                  int (*scheduleJob)(simulation *, int));

void calculateData(simulation *sim, const int *run, int quanta);

#endif //ASSIGNMENT2_RUN_H
