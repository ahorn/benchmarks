# Configure this 3 variables according to your computer environment
LLVM_GCC = llvm-gcc
LLVM_LD = llvm-ld
KLEE = klee
CBMC = cbmc
CC=gcc

SRC = *.c 
LLVM_BC = *.bc.o
INCLUDE = -I ./

VERDEF = -D_KLEE_ $(PROP)

ALL_PROP = -D_ETHOC_PROP_1_ \
           -D_ETHOC_TEST_1_ \
           -D_ETHOC_TEST_2_ \
           -D_ETHOC_TEST_3_ \
           -D_ETHOC_TEST_4_

ethoc-hw-concrete:
	@${CC} -g $(SRC) $(ALL_PROP)

ethoc-hw-cbmc:
	@${CBMC} $(SRC) $(ALL_PROP) -D_SYMBOLIC_EXECUTION_ -D_CBMC_

ethoc-hw-cbmc-test-1:
	@${CBMC} $(SRC) -D_ETHOC_PROP_1_ -D_ETHOC_TEST_1_ -D_SYMBOLIC_EXECUTION_ -D_CBMC_

ethoc-hw-cbmc-test-2:
	@${CBMC} $(SRC) -D_ETHOC_PROP_1_ -D_ETHOC_TEST_2_ -D_SYMBOLIC_EXECUTION_ -D_CBMC_

ethoc-hw-cbmc-test-3:
	@${CBMC} $(SRC) -D_ETHOC_PROP_1_ -D_ETHOC_TEST_3_ -D_SYMBOLIC_EXECUTION_ -D_CBMC_

ethoc-hw-cbmc-test-4:
	@${CBMC} $(SRC) -D_ETHOC_PROP_1_ -D_ETHOC_TEST_4_ -D_SYMBOLIC_EXECUTION_ -D_CBMC_

ethoc-hw-llvm-gcc:
	@echo ------------- Compiling with llvm_gcc:
	@$(LLVM_GCC) $(INCLUDE) --emit-llvm -g -c sys.c -o sys.bc.o $(VERDEF)
	@$(LLVM_GCC) $(INCLUDE) --emit-llvm -g -c cpu.c -o cpu.bc.o $(VERDEF)
	@$(LLVM_GCC) $(INCLUDE) --emit-llvm -g -c irq.c -o irq.bc.o $(VERDEF)
	@$(LLVM_GCC) $(INCLUDE) --emit-llvm -g -c net.c -o net.bc.o $(VERDEF)
	@$(LLVM_GCC) $(INCLUDE) --emit-llvm -g -c opencores_eth.c -o opencores_eth.bc.o $(VERDEF)
	@$(LLVM_GCC) $(INCLUDE) --emit-llvm -g -c opencores_eth-test.c -o opencores_eth-test.bc.o $(VERDEF)

ethoc-hw-llvm-ld:llvm-gcc
	@echo ------------- Linking with llvm-ld:
	@$(LLVM_LD) $(LLVM_BC) -o test

ethoc-hw-klee:	llvm-ld
	@echo ------------- Running klee:	
	@$(KLEE) --optimize --libc=uclibc test.bc	

ethoc-hw-clean-klee:
	@echo ------------- Clean folders:
	@rm -rf $(LLVM_BC) test.bc test 
