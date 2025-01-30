#include <assert.h>
#include "../vector.h"

VEC(int, I)

int main(void) {
	Ivec v = Ivec_create();
	assert(Ivec_reserve(&v, 10) == 0);
	for (int i = 0; i < 10; ++i) {
		assert(Ivec_push(&v, 0) == 0);
	}
	for (int i = 0; i < 10; ++i) {
		assert(Ivec_set(&v, i, i) == 0);
	}
	for (int i = 0; i < 10; ++i) {
		int value;
		assert(Ivec_get(&v, i, &value) == 0);
		assert(value == i);
	}
	assert(Ivec_get(&v, 11, NULL) == OUT_OF_BOUNDS);
	Ivec_clear(&v);
	assert(Ivec_get(&v, 5, NULL) == OUT_OF_BOUNDS);
	assert(Ivec_get(&v, 0, NULL) == OUT_OF_BOUNDS);
	Ivec_destroy(&v);
	return 0;
}
