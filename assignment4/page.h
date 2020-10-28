#ifndef ASSIGNMENT4_PAGE_H
#define ASSIGNMENT4_PAGE_H

#include "job.h"

class Job;

class Page {
public:
	
	Job  *job      = nullptr;
	Page *nextPage = nullptr;
	Page *prevPage = nullptr;
	
	bool allocated = false;
	
	int memorySection = -1;
	
};

#endif //ASSIGNMENT4_PAGE_H
