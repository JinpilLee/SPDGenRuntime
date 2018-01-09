all:
	clang -O3 -fno-inline -c main.c
	clang -O3 -fno-inline -c -mllvm -polly -mllvm -polly-enable-spdgen test.c
	clang -O3 test.o main.o ../libSPDGen.a -o exec

emit:
	clang -O3 -fno-inline -S -emit-llvm -mllvm -polly -mllvm -polly-enable-spdgen test.c

clean:
	rm -f *.ll *.o *.spd *.s exec
