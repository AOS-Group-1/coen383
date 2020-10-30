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
	lastRef = 0;
	pages   = Page::freePages.front();
	Page::freePages.pop_front();
	pages->job           = nullptr;
	pages->allocated     = true;
	pages->memorySection = 0;
	pages->lastUsed      = time;
	pages->n_ref         = 0;
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
			Page::freePages.push_back(page);
			nextPage = nextPage->nextPage;
		}
		// TODO: print exit
		return;
	}
	
	getNextMemory();
	// check for hits
	Page *nextPage         = pages;
	while (nextPage != nullptr) {
		if (nextPage->memorySection == lastRef) {
			// TODO: hit
			nextPage->lastUsed = time;
			nextPage->n_ref++;
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
	newPage->lastUsed      = time;
	newPage->n_ref         = 0;
	addPage(newPage);
}

// Access with job->getNextMemory()
void Job::getNextMemory() {
	int i;
	
	int r   = rand() % 10;
	if (r >= 0 && r < 7) {
		// Spacial Locality 70% case
		i = rand() % 3 - 1; // -1, 0, 1
	} else if (r >= 7 && r <= 9) {
		i = rand() % (this->pageSize - 3) + 2; // 2, 3, 4, ... pagesize - 3
	}
	// Handle wraparound with index to current or last accessed page
	lastRef = (lastRef + i) % pageSize;
}

void Job::addPage(Page *page) {
	page->job       = this;
	page->allocated = true;
	page->memorySection = lastRef;
	page->nextPage  = pages;
	pages->prevPage = page;
	pages = page;
}
