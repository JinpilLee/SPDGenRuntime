CC_CMD=clang -O3
CXX_CMD=clang++ -O3

all: main.c kernel.cpp
	$(CC_CMD) -fno-inline -c main.c
	$(CXX_CMD) -c kernel.cpp
	$(CC_CMD) test.o main.o ../libSPDGen.a -o exec

cpu_only: test.c main.c
	$(CC_CMD) test.c main.c -o exec

prepare: test.c
	clang -O3 -fno-inline -c -mllvm -polly -mllvm -polly-enable-spdgen test.c

ll_emit: test.c
	clang -O3 -fno-inline -S -emit-llvm -mllvm -polly -mllvm -polly-enable-spdgen test.c

clean:
	rm -f *.ll *.o *.spd *.s exec
