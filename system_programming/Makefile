CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -lm
LNFLAGS = -ansi -pedantic-errors -Wall -Wextra -o
ALLOBJECTS =  $(patsubst %.c,%.o,$(wildcard ./ds/src/*.c))
OBJECTS = $(filter-out %_test.o, $(ALLOBJECTS))
OBJECTSTOREMOVE = $(patsubst ./ds/src/%,%,$(OBJECTS))
TESTS = $(wildcard ./ds/src/*_test.c)
TESTSOUT = $(patsubst ./ds/src/%.c,./bin/%.out,$(TESTS))
HEADERS = $(wildcard ./ds/src/*.h)
OBJDIR = ./include ./lib

test: stack_calc.c stack.c stack_calc_test.c stack_calc.h
	$(CC) $(CFLAGS) $^
	
#%.o: %.c %.h | $(OBJDIR)
#	$(CC) $(CFLAGS) $<
