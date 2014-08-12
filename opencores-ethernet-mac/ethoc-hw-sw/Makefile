ETHOC_HW_SRC = ..
CBMC = cbmc

SRC = \
	*.c \
	$(ETHOC_HW_SRC)/sys.c \
	$(ETHOC_HW_SRC)/net.c \
	$(ETHOC_HW_SRC)/ethoc-hw.c

ethoc-fw-concrete:
	gcc -I $(ETHOC_HW_SRC) -lpthread -g $(SRC)

ethoc-fw-concrete-bug:
	gcc -I $(ETHOC_HW_SRC) -lpthread -D_EXPOSE_BUG_ -D_BUG_ -g $(SRC)

ethoc-fw-cbmc:
	@${CBMC} -I $(ETHOC_HW_SRC) -D_SYMBOLIC_EXECUTION_ -D_CBMC_ $(SRC)

ethoc-fw-cbmc-bug:
	@${CBMC} -I $(ETHOC_HW_SRC) -D_SYMBOLIC_EXECUTION_ -D_BUG_ -D_CBMC_ $(SRC)
