all:
	gcc -c src/*.c -std=c99 -I./include -Werror -Wall -pedantic-errors
	gcc *.o -o a.out -lcheck
	rm *.o
	gcc main.c -c -coverage
	gcov main.c
