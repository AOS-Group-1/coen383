#ifndef ASSIGNMENT4_PAGE_H
#define ASSIGNMENT4_PAGE_H

#include <list>

class Job;

class Page {
public:
	
	static std::list<Page *> pages;
	static std::list<Page *> freePages;
	
	Job  *job          = nullptr;
	int  memorySection = -1;
	bool allocated     = false;
	float firstUsed = 0;
	float lastUsed = 0;
	
	int n_ref = 0; // Number of times this page was referenced
	
	/**
	 * Generates count pages, placed in freePages as well
	 * @param count
	 */
	static void generatePages(int count);
	
	static void memoryMap();
	
	void allocate(Job *pJob, float time, int memory = 0);
	
	void reference(float time);
	
	void free();
	
};

#endif //ASSIGNMENT4_PAGE_H
