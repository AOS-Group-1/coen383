#include "page.h"
#include "job.h"

std::list<Page *> Page::pages     = {};
std::list<Page *> Page::freePages = {};

void Page::generatePages(int count) {
	pages     = {};
	freePages = {};
	
	for (int  i = 0; i < count; ++i) {
		pages.push_back(new Page());
	}
	for (auto page : Page::pages) {
		freePages.push_back(page);
	}
}

void Page::memoryMap() {

}

void Page::allocate(Job *pJob, float time, int memory) {
	if (allocated) {
		// remove reference for previous job
		job->pages.remove(this);
	}
	
	job           = pJob;
	memorySection = memory;
	allocated     = true;
	firstUsed	  = time;
	lastUsed      = time;
	n_ref         = 0;
	job->pages.push_back(this);
}

void Page::reference(float time) {
	lastUsed = time;
	n_ref++;
}

void Page::free() {
	job           = nullptr;
	memorySection = -1;
	allocated     = false;
	freePages.push_back(this);
}
