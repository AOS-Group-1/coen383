#ifndef ASSIGNMENT2_JOB_H
#define ASSIGNMENT2_JOB_H

typedef struct Process process;

struct Process {
	int    id;
	double arrival_time;
	double service_time;
	int    priority;
	double end_time;
	
	double turnaround_time;
	double waiting_time;
	double response_time;
};

process *generateJob(int arrival_time);

typedef struct Simulation simulation;

struct Simulation {
	process **jobs;
	int     totalJobs;
};

simulation *generateJobs(int count);

void resetJobStats(simulation *sim);

#endif //ASSIGNMENT2_JOB_H
