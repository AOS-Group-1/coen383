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
	pages = Page::freePages.front();
	Page::freePages.pop_front();
	started = true;
}

void Job::loop(Page *(*getPage)(), float time) {
	if (!started && !finished) return;
	
}

int Job::getNextMemory() {
	return 0;
}
