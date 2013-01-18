SRC = main.c mc146818rtc.c qemu-timer.c qverify.c rtc-verify.c

all:
	gcc ${SRC} -lrt

verify:
	cbmc ${SRC} --unwind 1 -D__NO_TIMER__ -DRTC_BENCHMARK_PROP_11

clean:
