SRC = irq.c  tmp105.c  tmp105-test.c
#PROP_NO = 21

all:
	gcc ${SRC}

# Add -D__EXPOSE_BUG__ if you want to expose the bug
verify:
	cbmc ${SRC} --unwind 2 -D__CBMC_TEST_HW__ -DI2C_BENCHMARK_PROP_${PROP_NO} #-D__EXPOSE_BUG__

clean:
