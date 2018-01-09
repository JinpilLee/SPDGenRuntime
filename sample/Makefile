all:
	clang -O3 -fno-inline -c main.c
	clang -O3 -fno-inline -c -mllvm -polly -mllvm -polly-enable-spdgen test.c
	clang -O3 test.o main.o ../libSPDGen.a -o exe

test:
	clang -O1 -S -emit-llvm test.c -o opt.ll
	opt -S -polly-canonicalize opt.ll -o can.ll
	opt -S -loop-extract can.ll -o test.ll
#	opt -polly-ast -analyze -q test.ll -polly-process-unprofitable
	opt -polly-scops -analyze -q test.ll -polly-process-unprofitable

clean:
	rm -f *.ll *.o *.spd exe
