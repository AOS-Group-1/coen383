#include "page.h"

std::list<Page *> Page::pages     = {};
std::list<Page *> Page::freePages = {};

void Page::generatePages(int count) {
	pages     = {};
	freePages = {};
	
	for (int  i = 0; i < count; ++i) {
		pages.push_back(new Page());
	}
	for (auto page : Page::pages) {
		freePages.push_back(page);
	}
}
