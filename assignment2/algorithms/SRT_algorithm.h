#ifndef ASSIGNMENT2_SRT_ALGORITHM_H
#define ASSIGNMENT2_SRT_ALGORITHM_H

#include "../job.h"

/**
 * Called when a new job arrives at specific quanta.
 *
 * @param job
 * @param quanta - quanta job is added in
 */
void SRT_Algorithm_Add(process *job, int quanta);

/**
 * Called at each quanta, should return job id of which job is decided upon for that quanta.
 *
 * @param quanta
 * @return job id that is decided on to be ran, -1 if none decided
 */
int SRT_Algorithm(int quanta);

#endif //ASSIGNMENT2_SRT_ALGORITHM_H
