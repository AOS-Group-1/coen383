#include <vector>
#include <list>
#include "job.h"

std::vector<Job *> jobs;
std::list<Page *>  pages;
std::list<Page *>  freePages;

int main(int argc, char *argv[]) {
	for (auto job : Job::generateJobs()) {
		jobs.push_back(job);
	}
	
	for (int  i = 0; i < 100; ++i) {
		pages.push_back(new Page());
	}
	for (auto page : pages) {
		freePages.push_back(page);
	}
	
	for (int i = 0; i < 600; ++i) {
		float     time = (float) i / 10;
		for (auto job : jobs) {
			if ((float) job->arrivalTime <= time) {
				job->startJob();
			}
			job->loop();
		}
	}
	
	return 0;
}
