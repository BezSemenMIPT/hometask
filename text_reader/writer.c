#include "writer.h"
#include "counter.h"

void print_info(table_t  tb) {
	uintptr_t v;
	void* k;
	iter_t it;
	iter_reset(&it);
	while (iter_each(&it, &tb, &k, &v)) {
		printf("%s (%u)\n", (const char*)k, (unsigned int)v);
	}
	table_clear(&tb);
}
