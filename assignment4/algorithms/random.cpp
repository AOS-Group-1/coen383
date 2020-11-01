#include "random.h"
#include <cstdlib>

Page *Random::getPage() {
	int count = 0, max = -1;
	int r = rand() % 100 + 1;
	Page *evict = nullptr;
    for(auto p: Page::pages){
        if(p->n_ref > 0 && count < r){
            max = p->n_ref;
            evict = p;
        }
        count++;
    }
	return evict;
}
