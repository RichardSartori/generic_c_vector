#include <assert.h>
#include "../vector.h"

VEC(int, I)

int main(void) {
	Ivec v = Ivec_create();
	assert(Ivec_is_empty(&v));
	Ivec_destroy(&v);
	return 0;
}
