#ifndef ASSIGNMENT2_ALGORITHM_H
#define ASSIGNMENT2_ALGORITHM_H

#include "job.h"

/**
 * Signals when a job has arrived.
 *
 * @param sim
 * @param job
 * @param quanta - quanta job is added in
 */
void FCFS_Algorithm_Add(simulation *sim, process *job, int quanta);

/**
 * Runs the algorithm, called for each quanta.
 *
 * @param sim
 * @param quanta
 * @return job id that is decided on to be ran, -1 if none decided
 */
int FCFS_Algorithm(simulation *sim, int quanta);

#endif //ASSIGNMENT2_ALGORITHM_H
