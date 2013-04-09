KLEE_PATH = /auto/scratch/lliang/klee-cde-package
KLEE_INCLUDE = $(KLEE_PATH)/cde-root/home/pgbovine/klee/include
LLVM_GCC = $(KLEE_PATH)/bin/llvm-gcc.cde
KLEE = $(KLEE_PATH)/bin/klee.cde
SRC = opencores_eth-test.c

VERDEF = -D_NO_CBMC_ATOMIC_ \
         -DETHOC_BENCHMARK_PROP_1 \
         -DETHOC_BENCHMARK_PROP_2 \
         -DETHOC_BENCHMARK_PROP_3 \
         -DETHOC_BENCHMARK_PROP_4 \
         -DETHOC_BENCHMARK_PROP_5 \
         -DETHOC_BENCHMARK_PROP_6 \
         -DETHOC_BENCHMARK_PROP_7 \

all:
	gcc -g *.c $(VERDEF) -DCONCRETE_EXECUTION

test.bc:
	@echo ------------- Compiling with LLVM_GCC:
	$(LLVM_GCC) -I . -I $(KLEE_INCLUDE)/ --emit-llvm -c -g $(SRC) -o $@ $(VERDEF)

klee:	test.bc
	@echo ------------- Running KLEE:	
	$(KLEE) --optimize --libc=uclibc $<	

clean:
	@echo ------------- Clean folers...
	rm -rf klee-* *.bc
