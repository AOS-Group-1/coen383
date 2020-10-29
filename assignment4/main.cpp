#include "job.h"
#include "algorithms/FIFO.h"
#include "algorithms/LRU.h"
#include "algorithms/LFU.h"
#include "algorithms/MFU.h"
#include "algorithms/random.h"

void run(Page *(*getPage)()) {
	Job::generateJobs(150);
	Page::generatePages(100);
	
	for (int i = 0; i < 600; ++i) {
		float     time = (float) i / 10;
		for (auto job : Job::jobs) {
			job->startJob(time);
			job->loop(getPage, time);
		}
	}
}

int main(int argc, char *argv[]) {
	run(FIFO::getPage);
	run(LRU::getPage);
	run(LFU::getPage);
	run(MFU::getPage);
	run(Random::getPage);
	
	return 0;
}
