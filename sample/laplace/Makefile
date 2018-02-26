OPT=-O3 -mllvm -polly -mllvm -polly-enable-spdgen

all:
	clang $(OPT) -c test.c
	clang test.o ../../libSPDGen.a -o test

IR:
	clang $(OPT) -S -emit-llvm test.c

clean:
	rm -f *.ll *.spd test test.o
