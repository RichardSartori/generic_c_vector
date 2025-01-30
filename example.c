#include <stdio.h>
#include "vector.h"

VEC(int, I)

int main(void) {
	Ivec vec = Ivec_create();
	Ivec_push(&vec, 42);
	Ivec_push(&vec, 69);
	for (int* ptr = Ivec_begin(&vec); ptr != Ivec_end(&vec); ++ptr) {
		printf("%d\n", *ptr);
	}
	Ivec_destroy(&vec);
	return 0;
}
