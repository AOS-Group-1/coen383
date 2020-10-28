#ifndef ASSIGNMENT4_JOB_H
#define ASSIGNMENT4_JOB_H

#include <string>
#include <list>
#include "page.h"

class Job {
public:
	
	std::string name;
	int         pageSize;
	int         arrivalTime;
	int         serviceDuration;
	
	Page *pages = nullptr;
	
	explicit Job(std::string id);
	
	static std::vector<Job *> generateJobs();
	
	/**
	 * Allocate first page
	 *
	 */
	void startJob();
	
	/**
	 * Calculates next memory section that will be accessed
	 */
	int getNextMemory();
	
	/**
	 * Gets next page section, called every .1 sec
	 */
	void loop();
	
};

#endif //ASSIGNMENT4_JOB_H
