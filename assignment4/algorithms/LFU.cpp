#include "LFU.h"

Page *LFU::getPage() {
	int  min    = __INT_MAX__;
	Page *evict = nullptr;
	
	for (auto p : Page::pages) {
		if (p->n_ref < min) {
			min   = p->n_ref;
			evict = p;
		}
	}
	return evict;
}
