#should be in ds
################
CC = gcc
gd = -g -fPIC -ansi -pedantic-errors -Wall -Wextra
gc = -fPIC -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -o3
SRC=$(wildcard src/*.c)
OUT = $(wildcard *.out)
LIB = $(wildcard libds/*.a)

OBJ_TMP= $(notdir $(SRC))
OBJ_TMP2=$(OBJ_TMP:.c=.o)
OBJ=$(addprefix obj/,$(OBJ_TMP2))

LIBDIR = ./libds

$(warning $(OBJ))

###############################################################################

.PHONY: gcc

gcc: scheduler_gc.out
	
scheduler_gc.out: libds/libds_gcc.so test/scheduler_test.c 
	$(CC) -o $@ $^ -I ./include/ -lds_gcc -L./libds 

$(LIBDIR)/libds_gcc.so: schedulergc.o src/libdsgcc.a
	$(CC) -shared -fPIC $^ -o $@ 
	
src/libdsgcc.a:
	make gcc -C ./src
	
schedulergc.o: scheduler.c
	$(CC) $(gc) -c -o $@ $^ -I ./include/
###############################################################################

.PHONY: gdd

gdd: scheduler_gd.out
	
scheduler_gd.out: test/scheduler_test.c libds/libds_gdd.so
	$(CC) -o $@ $< -ldl -Llibds -lds_gdd -I ./include/

$(LIBDIR)/libds_gdd.so: src/libdsgdd.a  schedulergd.o 
	$(CC) -shared -fPIC $^ -o $@ 

src/libdsgdd.a:
	make gdd -C ./src
	
schedulergd.o: schedulergd.c
	$(CC) $(gd) -c -o $@ $^ -I ./include/
###############################################################################

		
.PHONY: test_gc

test_gc:
	./scheduler_gc.out

.PHONY: test_gd

test_gd:
	./scheduler_gd.out


.PHONY: clean
	
clean:
	rm -rf $(wildcard *.o)
	rm -rf $(wildcard libds/*.so)
	make clean -C ./src






