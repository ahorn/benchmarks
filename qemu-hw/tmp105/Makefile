SRC = irq.c  tmp105.c  tmp105-test.c

all:
	gcc ${SRC}

verify:
	cbmc ${SRC} --unwind 4 -DI2C_BENCHMARK_PROP_21
