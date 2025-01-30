#include <assert.h>
#include "../vector.h"

VEC(int, I)

int main(void) {
	Ivec v = Ivec_create();
	assert(Ivec_reserve(&v, 10) == 0);
	assert(Ivec_begin(&v) == Ivec_end(&v));
	for (int i = 0; i < 10; ++i) {
		assert(Ivec_push(&v, i) == 0);
	}
	assert(Ivec_begin(&v) != Ivec_end(&v));
	int expected = 0;
	for (int* ptr = Ivec_begin(&v); ptr != Ivec_end(&v); ++ptr) {
		assert(*ptr == expected);
		++expected;
	}
	Ivec_clear(&v);
	assert(Ivec_begin(&v) == Ivec_end(&v));
	Ivec_destroy(&v);
	return 0;
}
