all:
	gcc -c -g src/*.c -coverage -std=c99 -I./include -Werror -Wall -pedantic-errors
	gcc *.o -o a.out -lcheck
	rm *.o
	gcov main.c
