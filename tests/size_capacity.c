#include <assert.h>
#include "../vector.h"

VEC(size_t, S)

int main(void) {
	Svec v = Svec_create();
	assert(Svec_is_empty(&v));
	assert(Svec_size(&v) == 0);
	for (size_t i = 1; i < 10; ++i) {
		assert(Svec_push(&v, i) == 0);
		assert(Svec_size(&v) == i);
		assert(v.capacity >= i);
	}
	Svec_destroy(&v);
	return 0;
}
