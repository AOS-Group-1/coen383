#ifndef ASSIGNMENT4_JOB_H
#define ASSIGNMENT4_JOB_H

#include <string>
#include <vector>
#include "page.h"

class Job {
public:
	
	static std::vector<Job *> jobs;
	
	std::string name;
	int         pageSize;
	int         arrivalTime;
	int         serviceDuration;
	bool        started  = false;
	bool        finished = false;
	
	float endTime;
	
	Page *pages = nullptr;
	
	explicit Job(std::string id);
	
	/**
	 * generates count jobs, sorted by arrival time
	 * @param count
	 */
	static void generateJobs(int count);
	
	/**
	 * Allocate first page
	 *
	 */
	void startJob(float time);
	
	/**
	 * Called every .1 sec
	 */
	void loop(Page *(*getPage)(), float time);
	
	/**
	 * Calculates next memory section that will be accessed
	 */
	int getNextMemory();
	
};

#endif //ASSIGNMENT4_JOB_H
