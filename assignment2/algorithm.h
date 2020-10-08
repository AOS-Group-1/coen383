#ifndef ASSIGNMENT2_ALGORITHM_H
#define ASSIGNMENT2_ALGORITHM_H

#include "job.h"

/**
 * Adds a job to the schedule.
 *
 * @param time
 * @param job null if no job arrived
 * @return job id that is decided on to schedule, -1 if none decided
 */
int basicAlgorithm(int time, process *job);

#endif //ASSIGNMENT2_ALGORITHM_H
