#include <assert.h>
#include "../vector.h"

VEC(int, I)

int main(void) {
	Ivec v = Ivec_create();
	assert(Ivec_pop(&v) == OUT_OF_BOUNDS);
	assert(Ivec_is_empty(&v));
	assert(Ivec_push(&v, 42) == 0);
	assert(!Ivec_is_empty(&v));
	assert(Ivec_pop(&v) == 0);
	assert(Ivec_is_empty(&v));
	for (int i = 0; i < 10; ++i) {
		assert(Ivec_push(&v, 42) == 0);
	}
	assert(!Ivec_is_empty(&v));
	for (int i = 0; i < 10; ++i) {
		assert(Ivec_pop(&v) == 0);
	}
	assert(Ivec_is_empty(&v));
	Ivec_destroy(&v);
	return 0;
}
