#include <stdlib.h>
#include "job.h"

struct Process *generateJob() {
	struct Process *job = malloc(sizeof(struct Process));
	job->arrival_time = rand() % 100; // will return num between 0 and 99
	job->service_time = (rand() % 11); // will return num between 0 and 10
	if (job->service_time == 0) job->service_time += 0.1f; // service_time = 0.1 .. 10
	job->priority = rand() % 4 + 1; // priority between 1 .. 4
	return job;
}

int processComparator(const void *v1, const void *v2) {
	const struct Process *p1 = *(struct Process **) v1;
	const struct Process *p2 = *(struct Process **) v2;
	return (int) (p1->arrival_time - p2->arrival_time);
}

struct Process **generateJobs(int count) {
	struct Process **jobs = malloc(sizeof(struct Process *) * count);
	
	for (int i = 0; i < count; ++i)
		jobs[i] = generateJob();
	qsort(jobs, count, sizeof(struct Process *), processComparator);
	for (int i = 0; i < count; ++i)
		jobs[i]->id = i + 'A';
	return jobs;
}
