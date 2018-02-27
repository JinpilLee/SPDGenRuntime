OPT=-O3
SPD_OPT=-mllvm -polly -mllvm -polly-enable-spdgen

all:
	clang $(OPT) -c main.c
	clang++ main.o fpga.o ../../libSPDGen.a -o test

OBJ:
	clang $(OPT) $(SPD_OPT) -c fpga.c

IR:
	clang $(OPT) $(SPD_OPT) -S -emit-llvm fpga.c

clean:
	rm -f test main.o
