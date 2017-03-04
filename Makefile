all:
	gcc -c src/*.c *.c -std=c99 -I./include -Werror -Wall -pedantic-errors
	gcc *.o -o a.out -lcheck
	rm *.o
	./a.out
	
	
