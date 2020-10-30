#include "LRU.h"

Page *LRU::getPage() {
	float lruTime = __INT_MAX__;
	Page *evict = nullptr;

	for(auto p: Page::pages) {
		if(p->lastUsed < lruTime) {
			lruTime = p->lastUsed;
			evict = p;
		}
	}
	return evict;
}
