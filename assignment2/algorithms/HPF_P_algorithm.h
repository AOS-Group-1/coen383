#ifndef ASSIGNMENT2_HPF_P_ALGORITHM_H
#define ASSIGNMENT2_HPF_P_ALGORITHM_H

#include "../job.h"

/**
 * Called when a new job arrives at specific quanta.
 *
 * @param job
 * @param quanta - quanta job is added in
 */
void HPF_P_Algorithm_Add(process *job, int quanta);

/**
 * Called at each quanta, should return job id of which job is decided upon for that quanta.
 *
 * @param quanta
 * @return job id that is decided on to be ran, -1 if none decided
 */
int HPF_P_Algorithm(int quanta);

void HPFP_clearQueue();

#endif //ASSIGNMENT2_HPF_P_ALGORITHM_H
