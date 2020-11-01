#include "random.h"
#include <cstdlib>

Page *Random::getPage() {
	int       count = 0;
	int       r     = rand() % Page::pages.size();
	for (auto p : Page::pages) {
		if (count++ == r) {
			return p;
		}
	}
}
