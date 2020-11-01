#include "FIFO.h"

Page *FIFO::getPage() {
	Page *evict = nullptr;
	evict = Page::pages.front();
	return evict;
}
