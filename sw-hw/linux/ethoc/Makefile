HW_SRC = ../../../qemu-hw
OPEN_ETH_SRC = $(HW_SRC)/ethoc

SRC = \
	*.c \
	$(OPEN_ETH_SRC)/sys.c \
	$(OPEN_ETH_SRC)/cpu.c \
	$(OPEN_ETH_SRC)/irq.c \
	$(OPEN_ETH_SRC)/net.c \
	$(OPEN_ETH_SRC)/opencores_eth.c

all:
	gcc -I $(HW_SRC) -g $(SRC)
