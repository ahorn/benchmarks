SRC = irq.c  tmp105.c  tmp105-test.c
#PROP_NO = 21

all:
	gcc ${SRC}

verify:
	cbmc ${SRC} --unwind 4 -DI2C_BENCHMARK_PROP_${PROP_NO}

clean:
