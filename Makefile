all:
	clang -O3 -c *.c
	clang++ -O3 -c *.cpp
	ar rcs libSPDGen.a *.o

clean:
	rm -f libSPDGen.a *.o
