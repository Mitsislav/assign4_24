###################################################
#
# file: Makefile
#
# @Author:   Ioannis Chatziantoniou
# @Version:  9-4-2024
# @email:    csd5193@csd.uoc.gr
#
# Makefile
#
####################################################

all: sudoku

sudoku: grid.o sudoku.o
	gcc grid.o sudoku.o -o sudoku


grid.o: grid.c grid.h
	gcc -Wall -ansi -pedantic -c grid.c

sudoku.o: sudoku.c sudoku.h
	gcc -Wall -ansi -pedantic -c sudoku.c

clean:
	rm -f *.o
	rm -f sudoku
	rm -f example.txt


