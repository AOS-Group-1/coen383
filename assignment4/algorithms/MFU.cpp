#include "MFU.h"

Page *MFU::getPage() {
    int max = -1;
    Page *evict = nullptr;

    for(auto &&p : Page::pages){
        if(p->n_ref > max){
            max = p->n_ref;
            evict = p;
        }
    }
	return evict;
}
