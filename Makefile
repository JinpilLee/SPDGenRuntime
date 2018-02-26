all:
	clang -O3 -c *.c *.cpp
	ar rcs libSPDGen.a *.o

clean:
	rm -f libSPDGen.a *.o
