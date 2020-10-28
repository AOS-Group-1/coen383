#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include "job.h"

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

std::vector<Job *> Job::generateJobs() {
	std::vector<Job *> jobs;
	
	for (int i = 0; i < 150; ++i) {
		std::string id;
		id.push_back('A' + (i / 26));
		id.push_back('A' + (i % 26));
		jobs.push_back(new Job(id));
	}
	
	std::sort(jobs.begin(), jobs.end(), cmp);
	return jobs;
}
