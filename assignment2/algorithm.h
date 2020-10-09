#ifndef ASSIGNMENT2_ALGORITHM_H
#define ASSIGNMENT2_ALGORITHM_H

#include "job.h"

/**
 * Runs the algorithm on the time slice.
 * Will be called for each time slice and start of each job.
 * If multiple jobs start at the same time slice, will be called twice for that time slice.
 *
 * @param time
 * @param job - null if no job arrived
 * @return job id that is decided on to be ran, -1 if none decided
 */
int FCFS_Algorithm(simulation *sim, int time, process *job);

#endif //ASSIGNMENT2_ALGORITHM_H
