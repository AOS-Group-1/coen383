#ifndef ASSIGNMENT2_SJF_ALGORITHM_H
#define ASSIGNMENT2_SJF_ALGORITHM_H

#include "../job.h"

#include "priority_queue.h"


/**
 * Called when a new job arrives at specific quanta.
 *
 * @param job
 * @param quanta - quanta job is added in
 */
void SJF_Algorithm_Add(process *job, int quanta);

/**
 * Called at each quanta, should return job id of which job is decided upon for that quanta.
 *
 * @param quanta
 * @return job id that is decided on to be ran, -1 if none decided
 */
int SJF_Algorithm(int quanta);

void SJF_clearQueue();

#endif //ASSIGNMENT2_SJF_ALGORITHM_H
