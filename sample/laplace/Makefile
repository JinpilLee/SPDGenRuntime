OPT=-O3 -std=c99

all:
	gcc $(OPT) -c main.c
	g++ main.o fpga.o ../../libSPDGen.a -o test

clean:
	rm -f test *.o *.spd

# XXX for internal use
# requires modified LLVM compiler
SPD_OPT=-mllvm -polly -mllvm -polly-enable-spdgen

OBJ:
	clang $(OPT) $(SPD_OPT) -c fpga.c

IR:
	clang $(OPT) $(SPD_OPT) -S -emit-llvm fpga.c
