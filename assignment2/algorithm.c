#include "algorithm.h"

int basicAlgorithm(int time, process *job) {
	if (job)
		return job->id;
	else
		return -1;
}
