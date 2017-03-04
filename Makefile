all:
	gcc -c -g src/*.c -std=c99 -I./include -Werror -Wall -pedantic-errors -coverage O0
	gcc *.o -o a.out -lcheck
	rm *.o
	./a.out
	gcov main.c
