all:
	gcc -c src/*.c -coverage -std=c99 -I./include -Werror -Wall -pedantic-errors
	gcc *.o -o a.out -lcheck
	rm *.o
