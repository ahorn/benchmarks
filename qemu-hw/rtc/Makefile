all:
	gcc *.c -lrt

verify:
	cbmc *.c --unwind 1
