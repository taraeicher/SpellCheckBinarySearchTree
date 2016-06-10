CC=gcc -Wall -lm

all: spellcheck

spellcheck: set.o bin_search_tree.o spellcheck.h spellcheck.c
	$(CC) -o spellcheck spellcheck.c set.o bin_search_tree.o

bin_search_tree.o: bin_search_tree.h bin_search_tree.c
	$(CC) -c bin_search_tree.c

set.o: set.h set.c 
	$(CC) -c set.c 

tidy :
	rm -f bin_search_tree.o set.o core

clean :
	rm -f spellcheck bin_search_tree.o set.o core
