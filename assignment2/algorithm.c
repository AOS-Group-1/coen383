#include "algorithm.h"

int basicAlgorithm(int time, struct Process *job) {
	if (job)
		return job->id;
	else
		return -1;
}
