#include <stdlib.h>
#include <math.h>
#include "job.h"

process *generateJob(int arrival_time) {
	process *job = malloc(sizeof(process));
	if (arrival_time != -1)
		job->arrival_time = arrival_time;
	else
		job->arrival_time = rand() % 100; // will return num between 0 and 99
	job->service_time     = (rand() % 11); // will return num between 0 and 10
	if (job->service_time == 0) job->service_time += 0.1f; // service_time = 0.1 .. 10
	job->priority = rand() % 4 + 1; // priority between 1 .. 4
	return job;
}

int processComparator(const void *v1, const void *v2) {
	const process *p1 = *(process **) v1;
	const process *p2 = *(process **) v2;
	return (int) (p1->arrival_time - p2->arrival_time);
}

simulation *generateJobs(int count) {
	simulation *sim = malloc(sizeof(simulation *));
	sim->jobs      = malloc(sizeof(process *) * count);
	sim->totalJobs = count;
	
	for (int i = 0; i < sim->totalJobs; ++i)
		sim->jobs[i] = generateJob(-1);
	qsort(sim->jobs, sim->totalJobs, sizeof(process *), processComparator);
	
	int finished;
	do {
		finished         = 1;
		double last_time = sim->jobs[0]->arrival_time;
		
		for (int i = 0; i < sim->totalJobs; ++i) {
			process *job = sim->jobs[i];
			if (last_time + 1 < job->arrival_time) {
				sim->jobs = realloc(sim->jobs, sizeof(process *) * ++sim->totalJobs);
				sim->jobs[sim->totalJobs - 1] = generateJob((int) last_time + 1);
				finished = 0;
				break;
			} else {
				last_time = fmax(job->arrival_time + job->service_time, last_time);
			}
		}
		qsort(sim->jobs, sim->totalJobs, sizeof(process *), processComparator);
	} while (!finished);
	
	for (int i = 0; i < sim->totalJobs; ++i)
		sim->jobs[i]->id = i + 'A';
	resetJobStats(sim);
	return sim;
}

void resetJobStats(simulation *sim) {
	for (int i = 0; i < sim->totalJobs; ++i) {
		process *job = sim->jobs[i];
		job->end_time        = 0;
		job->waiting_time    = 0;
		job->turnaround_time = 0;
		job->response_time   = 0;
	}
}
