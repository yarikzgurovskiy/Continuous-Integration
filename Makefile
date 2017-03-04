all:
	gcc -c -g src/*.c -std=c99 -I./include -Werror -Wall -pedantic-errors
	gcc *.o -o a.out -lprogbase -lcheck
	rm *.o