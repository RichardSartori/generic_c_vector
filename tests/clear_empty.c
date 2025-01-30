#include <assert.h>
#include "../vector.h"

VEC(int, I)

int main(void) {
	Ivec v = Ivec_create();
	assert(Ivec_is_empty(&v));
	assert(Ivec_reserve(&v, 10) == 0);
	assert(Ivec_is_empty(&v));
	assert(Ivec_push(&v, 42) == 0);
	assert(Ivec_push(&v, 69) == 0);
	assert(!Ivec_is_empty(&v));
	Ivec_clear(&v);
	assert(Ivec_is_empty(&v));
	Ivec_clear(&v);
	assert(Ivec_is_empty(&v));
	Ivec_destroy(&v);
	return 0;
}
