#include <algorithm>
#include "job.h"

std::vector<Job *> Job::jobs = {};

Job::Job(std::string id) {
	name = std::move(id);
	std::vector<int> pageSizes{5, 11, 17, 31};
	pageSize        = pageSizes.at(rand() % pageSizes.size());
	arrivalTime     = rand() % 60;
	serviceDuration = rand() % 5 + 1;
}

bool cmp(Job *a, Job *b) {
	return a->arrivalTime < b->arrivalTime;
}

void Job::generateJobs(int count) {
	jobs = {};
	
	for (int i = 0; i < count; ++i) {
		std::string id;
		id.push_back('A' + (i / 26));
		id.push_back('A' + (i % 26));
		jobs.push_back(new Job(id));
	}
	
	std::sort(jobs.begin(), jobs.end(), cmp);
}

void Job::startJob(float time) {
	if (started || (float) arrivalTime > time || Page::freePages.size() < 4) return;
	endTime = time + (float) serviceDuration;
	pages   = Page::freePages.front();
	Page::freePages.pop_front();
	pages->job           = nullptr;
	pages->allocated     = true;
	pages->memorySection = 0;
	pages->lastUsed      = time;
	started = true;
	// TODO: print enter
}

void Job::loop(Page *(*getPage)(), float time) {
	if (!started || finished) return;
	if (endTime <= time) {
		finished = true;
		Page *nextPage = pages;
		while (nextPage != nullptr) {
			Page *page = nextPage;
			page->job           = nullptr;
			page->nextPage      = nullptr;
			page->prevPage      = nullptr;
			page->allocated     = false;
			page->memorySection = -1;
			page->lastUsed      = time;
			nextPage = nextPage->nextPage;
		}
		// TODO: print exit
		return;
	}
	
	int  newMem       = getNextMemory();
	// check for hits
	Page *nextPage    = pages;
	while (nextPage != nullptr) {
		if (pages->memorySection == newMem) {
			// TODO: hit
			return;
		}
		nextPage = nextPage->nextPage;
	}
	// TODO: miss
	
	Page *newPage;
	// get from free pages if there are any
	if (!Page::freePages.empty()) {
		newPage = Page::freePages.front();
		Page::freePages.pop_front();
	} else {
		// get from all pages
		newPage = getPage();
		newPage->prevPage->nextPage = newPage->nextPage;
		newPage->nextPage->prevPage = newPage->prevPage;
	}
	// TODO: print page change
	newPage->nextPage = pages;
	pages->prevPage   = newPage;
	pages = newPage;
	pages->job           = this;
	pages->memorySection = newMem;
	pages->lastUsed      = time;
}

int Job::getNextMemory() {
	return 0;
}
