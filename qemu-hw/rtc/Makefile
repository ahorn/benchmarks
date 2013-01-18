SRC = main.c mc146818rtc.c qemu-timer.c qverify.c rtc-verify.c
PROP_NO = 11

all:
	gcc ${SRC} -lrt

verify:
	cbmc ${SRC} --unwind 1 -D__NO_TIMER__ -DRTC_BENCHMARK_PROP_$(PROP_NO)

clean:
