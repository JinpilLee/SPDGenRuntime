all:
	clang -O3 -c *.c
	ar rcs libSPDGen.a *.o

clean:
	rm -f *.o
