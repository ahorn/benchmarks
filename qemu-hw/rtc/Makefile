SRC = main.c mc146818rtc.c qemu-timer.c qverify.c rtc-verify.c
#PROP_NO = 2
#UNWIND = 11

all:
	gcc ${SRC} -lrt

# Add -D__EXPOSE_BUG__ if you want to expose the bug
verify:
	cbmc ${SRC} --unwind $(UNWIND) -D__CBMC_TEST_HW__ -D__NO_TIMER__ -DRTC_BENCHMARK_PROP_$(PROP_NO) #-D__EXPOSE_BUG__ 

clean:
