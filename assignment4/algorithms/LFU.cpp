#include "LFU.h"

Page *LFU::getPage() {
	int  min    = 0;
	Page *evict = nullptr;
	
	for (auto p : Page::pages) {
		if (p->n_ref < min) {
			min   = p->n_ref;
			evict = p;
		}
	}
	return evict;
}
