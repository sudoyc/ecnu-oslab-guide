run: spinlock.c test.c spinlock.h
	gcc -Wall -Wextra -O1 -pthread spinlock.c test.c -o test
	./test

clean:
	rm -f test

.PHONY: run clean
