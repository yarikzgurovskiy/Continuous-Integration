all:
	gcc -c -g src/*.c -std=c99 -I./include -Werror -Wall -pedantic-errors -coverage
	gcc *.o -o a.out -lcheck
	rm *.o
