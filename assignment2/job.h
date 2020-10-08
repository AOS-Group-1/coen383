#ifndef ASSIGNMENT2_JOB_H
#define ASSIGNMENT2_JOB_H

struct Process {
	int    id;
	double arrival_time;
	double service_time;
	int    priority;
	
	double turnaround_time;
	double waiting_time;
	double response_time;
};

struct Process *generateJob();

struct Process **generateJobs(int count);

#endif //ASSIGNMENT2_JOB_H
