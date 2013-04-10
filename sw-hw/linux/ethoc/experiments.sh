#!/bin/bash

GOTO_CC=/nas/mictau/from-clpc8/cprover.git/src/goto-cc/goto-cc
GOTO_INSTRUMENT=/nas/mictau/from-clpc8/cprover.git/src/goto-instrument/goto-instrument
CBMC=/nas/mictau/from-clpc8/cprover.git/src/cbmc/cbmc

echo "SLOCCount says:"
sloccount *.c *.h ../../../qemu-hw/ethoc/*.h ../../../qemu-hw/ethoc/{opencores_eth,irq,cpu}.c | grep "^Total Physical"

$GOTO_CC -m32 ../../../qemu-hw/ethoc/{cpu.c,irq.c,opencores_eth.c} *.c \
  -I../../../qemu-hw -D_CBMC_ -D__CPROVER_ASYNC_1=XXX \
  -DETHOC_BENCHMARK_PROP_5 \
  -o ethoc_sw_hw_m32_sequential_prop5.gb
$GOTO_INSTRUMENT --count-eloc ethoc_sw_hw_m32_sequential_prop5.gb
$GOTO_CC -m32 ../../../qemu-hw/ethoc/{cpu.c,irq.c,opencores_eth.c} *.c \
  -I../../../qemu-hw -D_CBMC_ -D__CPROVER_ASYNC_1=XXX \
  -DETHOC_BENCHMARK_PROP_6 \
  -o ethoc_sw_hw_m32_sequential_prop6.gb
$GOTO_INSTRUMENT --count-eloc ethoc_sw_hw_m32_sequential_prop6.gb
$GOTO_CC -m32 ../../../qemu-hw/ethoc/{cpu.c,irq.c,opencores_eth.c} *.c \
  -I../../../qemu-hw -D_CBMC_ -D__CPROVER_ASYNC_1=XXX \
  -DETHOC_BENCHMARK_PROP_7 \
  -o ethoc_sw_hw_m32_sequential_prop7.gb
$GOTO_INSTRUMENT --count-eloc ethoc_sw_hw_m32_sequential_prop7.gb

$GOTO_CC -m32 ../../../qemu-hw/ethoc/{cpu.c,irq.c,opencores_eth.c} *.c \
  -I../../../qemu-hw -D_CBMC_ \
  -DETHOC_BENCHMARK_PROP_5 \
  -o ethoc_sw_hw_m32_prop5.gb
$GOTO_INSTRUMENT --count-eloc ethoc_sw_hw_m32_prop5.gb
$GOTO_CC -m32 ../../../qemu-hw/ethoc/{cpu.c,irq.c,opencores_eth.c} *.c \
  -I../../../qemu-hw -D_CBMC_ \
  -DETHOC_BENCHMARK_PROP_6 \
  -o ethoc_sw_hw_m32_prop6.gb
$GOTO_INSTRUMENT --count-eloc ethoc_sw_hw_m32_prop6.gb
$GOTO_CC -m32 ../../../qemu-hw/ethoc/{cpu.c,irq.c,opencores_eth.c} *.c \
  -I../../../qemu-hw -D_CBMC_ \
  -DETHOC_BENCHMARK_PROP_7 \
  -o ethoc_sw_hw_m32_prop7.gb
$GOTO_INSTRUMENT --count-eloc ethoc_sw_hw_m32_prop7.gb


mkdir -p results.cbmc
cd results.cbmc
rm -rf results.txt ethoc-sw-hw.web

cpbm run --cmd $CBMC ../ethoc_sw_hw_m32_sequential_prop5.gb -- \
  --unwind 1 --partial-loops --no-unwinding-assertions >> results.txt
cpbm run --cmd $CBMC ../ethoc_sw_hw_m32_sequential_prop6.gb -- \
  --unwind 1 --partial-loops --no-unwinding-assertions >> results.txt
cpbm run --cmd $CBMC ../ethoc_sw_hw_m32_sequential_prop7.gb -- \
  --unwind 1 --partial-loops --no-unwinding-assertions >> results.txt

cpbm run --cmd $CBMC ../ethoc_sw_hw_m32_prop5.gb -- \
  --unwind 1 --partial-loops --no-unwinding-assertions >> results.txt
cpbm run --cmd $CBMC ../ethoc_sw_hw_m32_prop6.gb -- \
  --unwind 1 --partial-loops --no-unwinding-assertions >> results.txt
cpbm run --cmd $CBMC ../ethoc_sw_hw_m32_prop7.gb -- \
  --unwind 1 --partial-loops --no-unwinding-assertions >> results.txt

cpbm csv cbmc results.txt > results.csv
cpbm web results.csv ethoc-sw-hw.web
chmod -R a+rX ethoc-sw-hw.web
