#ifndef ASSIGNMENT2_SRT_ALGORITHM_H
#define ASSIGNMENT2_SRT_ALGORITHM_H

#include "../job.h"

/**
 * Signals when a job has arrived.
 *
 * @param job
 * @param quanta - quanta job is added in
 */
void SRT_Algorithm_Add(process *job, int quanta);

/**
 * Runs the algorithm, called for each quanta.
 *
 * @param quanta
 * @return job id that is decided on to be ran, -1 if none decided
 */
int SRT_Algorithm(int quanta);

void SRT_clearQueue();

#endif //ASSIGNMENT2_SRT_ALGORITHM_H
