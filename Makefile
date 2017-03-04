all:
	clang -c src/*.c -std=c99 -I./include -Werror -Wall -pedantic-errors
	clang *.o -o a.out -lcheck
	rm *.o
