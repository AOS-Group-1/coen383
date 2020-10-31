#include <algorithm>
#include "job.h"

std::vector<Job *> Job::jobs = {};

int Job::hits      = 0;
int Job::misses    = 0;
int Job::successes = 0;

Job::Job() {
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
		jobs.push_back(new Job());
	}
	
	std::sort(jobs.begin(), jobs.end(), cmp);
	
	int       i = 0;
	for (auto job : Job::jobs) {
		job->name.push_back('A' + (i / 26));
		job->name.push_back('A' + (i % 26));
		i++;
	}
}

void Job::startJob(float time) {
	if (started || (float) arrivalTime > time || Page::freePages.size() < 4) return;
	endTime = time + (float) serviceDuration;
	lastRef = 0;
	Page::freePages.front()->allocate(this, time);
	Page::freePages.pop_front();
	started = true;
	successes++;
	// print enter
	printf("%.1f,\t%s,\tenter,\t\t%i,\t\t%i\n", time, name.c_str(), pageSize, serviceDuration);
}

void Job::loop(Page *(*getPage)(), float time) {
	if (!started || finished) return;
	if (endTime <= time) {
		finished = true;
		for (auto page : pages) {
			page->free();
		}
		pages.clear();
		// print exit
		printf("%.1f,\t%s,\texit,\t\t%i,\t\t%i\n", time, name.c_str(), pageSize, serviceDuration);
		return;
	}
	
	getNextMemory();
	// check for hits
	for (auto page : pages) {
		if (page->memorySection == lastRef) {
			// hit
			page->reference(time);
			hits++;
			return;
		}
	}
	// miss
	misses++;
	
	Page *newPage;
	// get from free pages if there are any
	if (!Page::freePages.empty()) {
		newPage = Page::freePages.front();
		Page::freePages.pop_front();
		// print page from free
		printf("%.1f,\t%s,\tfalse\n", time, name.c_str());
	} else {
		// get from all pages
		newPage = getPage();
		// print page change from allocated
		printf("%.1f,\t%s,\ttrue,\t\t%s,\t\t%i\n",
		       time, name.c_str(), newPage->job->name.c_str(), newPage->memorySection);
	}
	newPage->allocate(this, time, lastRef);
}

// Access with job->getNextMemory()
void Job::getNextMemory() {
	int i;
	
	int r   = rand() % 10;
	if (r >= 0 && r < 7) {
		// Spacial Locality 70% case
		i = rand() % 3 - 1; // -1, 0, 1
	} else if (r >= 7 && r <= 9) {
		i = rand() % (pageSize - 3) + 2; // 2, 3, 4, ... pagesize - 3
	}
	// Handle wraparound with index to current or last accessed page
	lastRef = (lastRef + i + pageSize) % pageSize;
}
