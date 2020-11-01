#include <iostream>
#include <ctime>
#include "job.h"
#include "algorithms/FIFO.h"
#include "algorithms/LRU.h"
#include "algorithms/LFU.h"
#include "algorithms/MFU.h"
#include "algorithms/random.h"

int totalHits[5]      = {0};
int totalMisses[5]    = {0};
int totalSuccesses[5] = {0};

void run(Page *(*getPage)(), int val) {
	Job::generateJobs(150);
	Page::generatePages(100);
	Job::hits      = 0;
	Job::misses    = 0;
	Job::successes = 0;
	printf("Time  | Job   | Status|    Page Size     |   Service Time\n");
	printf("********************************************************\n");
	for (int i     = 0; i < 600; ++i) {
		float     time = (float) i / 10;
		for (auto job : Job::jobs) {
			job->startJob(time);
			job->loop(getPage, time);
		}
	}
	totalHits[val] += Job::hits;
	totalMisses[val] += Job::misses;
	totalSuccesses[val] += Job::successes;
	std::cout << "hit/miss ratio: " << (float) Job::hits / (float) (Job::hits + Job::misses)
	          << std::endl;
}

void runMultiple(Page *(*getPage)(), int count, int val) {
	for (int i = 0; i < count; i++) {
		run(getPage, val);
	}
	totalHits[val] /= count;
	totalMisses[val] /= count;
	totalSuccesses[val] /= count;
}

int main(int argc, char *argv[]) {
	int seed = time(nullptr);
	srand(seed);
	printf("********************************************************\n");
	std::cout << "FIFO" << std::endl;
	printf("********************************************************\n");
	runMultiple(FIFO::getPage, 5, 0);
	srand(seed);
	printf("********************************************************\n");
	std::cout << "LRU" << std::endl;
	printf("********************************************************\n");
	runMultiple(LRU::getPage, 5, 1);
	srand(seed);
	printf("********************************************************\n");
	std::cout << "LFU" << std::endl;
	printf("********************************************************\n");
	runMultiple(LFU::getPage, 5, 2);
	srand(seed);
	printf("********************************************************\n");
	std::cout << "MFU" << std::endl;
	printf("********************************************************\n");
	runMultiple(MFU::getPage, 5, 3);
	srand(seed);
	printf("********************************************************\n");
	std::cout << "Random" << std::endl;
	printf("********************************************************\n");
	runMultiple(Random::getPage, 5, 4);
	
	std::cout << std::endl;
	std::cout << "FIFO average hit/miss ratio: "
	          << (float) totalHits[0] / (float) (totalHits[0] + totalMisses[0])
	          << std::endl;
	std::cout << "FIFO average swapped in: " << totalSuccesses[0] << std::endl;
	std::cout << "LRU average hit/miss ratio: "
	          << (float) totalHits[1] / (float) (totalHits[1] + totalMisses[1])
	          << std::endl;
	std::cout << "LRU average swapped in: " << totalSuccesses[1] << std::endl;
	std::cout << "LFU average hit/miss ratio: "
	          << (float) totalHits[2] / (float) (totalHits[2] + totalMisses[2])
	          << std::endl;
	std::cout << "LFU average swapped in: " << totalSuccesses[2] << std::endl;
	std::cout << "MFU average hit/miss ratio: "
	          << (float) totalHits[3] / (float) (totalHits[3] + totalMisses[3])
	          << std::endl;
	std::cout << "MFU average swapped in: " << totalSuccesses[3] << std::endl;
	std::cout << "Random average hit/miss ratio: "
	          << (float) totalHits[4] / (float) (totalHits[4] + totalMisses[4])
	          << std::endl;
	std::cout << "Random average swapped in: " << totalSuccesses[4] << std::endl;
	
	return 0;
}
