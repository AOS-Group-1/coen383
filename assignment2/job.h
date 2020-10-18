#ifndef ASSIGNMENT2_JOB_H
#define ASSIGNMENT2_JOB_H

typedef struct {
	int    id;
	double arrival_time;
	double service_time;
	int    priority;
	double end_time;
	double remaining_time;
	
	double turnaround_time;
	double waiting_time;
	double response_time;
} process;

void generateJob(process *job, int arrival_time);

typedef struct {
	process *jobs;
	int     totalJobs;
} simulation;

simulation *generateJobs(int count);

void resetJobStats(simulation *sim);

#endif //ASSIGNMENT2_JOB_H
