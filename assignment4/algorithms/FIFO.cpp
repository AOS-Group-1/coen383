#include "FIFO.h"

Page *FIFO::getPage() {
	float FIFOTime = __INT_MAX__;
	Page  *evict  = nullptr;
	
	for (auto p: Page::pages) {
		
		if (p->firstUsed < FIFOTime) {
			FIFOTime = p->firstUsed;
			evict   = p;
		}
	}
	return evict;
}
