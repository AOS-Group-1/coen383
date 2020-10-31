#include <iostream>
#include "job.h"
#include "algorithms/FIFO.h"
#include "algorithms/LRU.h"
#include "algorithms/LFU.h"
#include "algorithms/MFU.h"
#include "algorithms/random.h"

int totalHits      = 0;
int totalMisses    = 0;
int totalSuccesses = 0;

void run(Page *(*getPage)()) {
	Job::generateJobs(150);
	Page::generatePages(100);
	Job::hits      = 0;
	Job::misses    = 0;
	Job::successes = 0;
	printf("Time  | Job   | Status|    Page Size     |   Service Time\n");
	printf("********************************************************\n");
	for (int i = 0; i < 600; ++i) {
		float     time = (float) i / 10;
		for (auto job : Job::jobs) {
			job->startJob(time);
			job->loop(getPage, time);
		}
	}
	totalHits += Job::hits;
	totalMisses += Job::misses;
	totalSuccesses += Job::successes;
	std::cout << "hit/miss ratio: " << (float) Job::hits / (float) Job::misses << std::endl;
}

void runMultiple(Page *(*getPage)(), int count) {
	totalHits   = 0;
	totalMisses = 0;
	for (int i  = 0; i < count; i++) {
		run(getPage);
	}
	totalHits /= count;
	totalMisses /= count;
	std::cout << "average hit/miss ratio: " << (float) totalHits / (float) totalMisses << std::endl;
	std::cout << "average swapped in: " << totalSuccesses << std::endl << std::endl;
}

int main(int argc, char *argv[]) {
	printf("********************************************************\n");
	std::cout << "FIFO" << std::endl;
	printf("********************************************************\n");
	runMultiple(FIFO::getPage, 5);
	printf("********************************************************\n");
	std::cout << "LRU" << std::endl;
	printf("********************************************************\n");
	runMultiple(LRU::getPage, 5);
	printf("********************************************************\n");
	std::cout << "LFU" << std::endl;
	printf("********************************************************\n");
	runMultiple(LFU::getPage, 5);
	printf("********************************************************\n");
	std::cout << "MFU" << std::endl;
	printf("********************************************************\n");
	runMultiple(MFU::getPage, 5);
	printf("********************************************************\n");
	std::cout << "Random" << std::endl;
	printf("********************************************************\n");
	runMultiple(Random::getPage, 5);
	
	return 0;
}
