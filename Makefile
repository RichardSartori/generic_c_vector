CFLAGS = -std=c99 -Wall -Wextra -Werror -fmax-errors=1

TEST_SRCS = $(wildcard tests/*.c)
TEST_BINS = $(patsubst %.c, %, $(TEST_SRCS))

default: example

all: example $(TEST_BINS)

test: $(TEST_BINS)
	@set -e ; \
	for test in $(TEST_BINS) ; do \
		valgrind --leak-check=yes --error-exitcode=1 ./$$test ; \
	done

%: %.c vector.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f example $(TEST_BINS)

.PHONY: all clean default test
