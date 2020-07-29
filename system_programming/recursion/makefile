recursion.out: recursion.o recursion_test.o
	gcc recursion_test.o recursion.o ../../ds/lib/data_structures.a -o recursion.out

recursion_test.o: recursion_test.c recursion.o
	gcc -c -Wall -Wextra -pedantic-errors -ansi -g recursion_test.c -I../../ds/include/

recursion.o: recursion.c recursion.h 
	gcc -c -Wall -Wextra -pedantic-errors -ansi -g recursion.c -I../../ds/include/
