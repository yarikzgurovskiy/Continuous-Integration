all:
	gcc -c -g src/*.c -std=c99 -I./include -Werror -Wall -pedantic-errors -coverage gcov main.c
	gcc *.o -o a.out -lcheck
	rm *.o
	./a.out
	gcov main.c
