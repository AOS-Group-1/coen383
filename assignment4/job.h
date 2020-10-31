#ifndef ASSIGNMENT4_JOB_H
#define ASSIGNMENT4_JOB_H

#include <string>
#include <vector>
#include "page.h"

class Job {
public:
	
	static std::vector<Job *> jobs;
	
	static int hits;
	static int misses;
	static int successes;
	
	std::string name;
	int         pageSize;
	int         arrivalTime;
	int         serviceDuration;
	bool        started  = false;
	bool        finished = false;
	
	float endTime = 0;
	int   lastRef = 0;
	
	Page *pages = nullptr;
	
	explicit Job();
	
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
	 * Calculates next memory section that will be accessed into lastRef
	 */
	void getNextMemory();
	
};

#endif //ASSIGNMENT4_JOB_H
