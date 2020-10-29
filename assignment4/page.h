#ifndef ASSIGNMENT4_PAGE_H
#define ASSIGNMENT4_PAGE_H

#include <list>

class Job;

class Page {
public:
	
	static std::list<Page *> pages;
	static std::list<Page *> freePages;
	
	Job  *job      = nullptr;
	Page *nextPage = nullptr;
	Page *prevPage = nullptr;
	
	bool allocated     = false;
	int  memorySection = -1;
	
	float lastUsed = 0;

	int n_ref = 0; // Number of times this page was referenced
	
	/**
	 * Generates count pages, placed in freePages as well
	 * @param count
	 */
	static void generatePages(int count);
	
};

#endif //ASSIGNMENT4_PAGE_H
