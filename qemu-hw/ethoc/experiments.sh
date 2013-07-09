#!/bin/bash

GOTO_CC=/nas/mictau/from-clpc8/benchmarks/goto-cc
GOTO_INSTRUMENT=/nas/mictau/from-clpc8/benchmarks/goto-instrument
CBMC=/nas/mictau/from-clpc8/benchmarks/cbmc

echo "SLOCCount says:"
sloccount *.h opencores_eth-test.c opencores_eth.c irq.c cpu.c | grep "^Total Physical"

$GOTO_CC -m32 opencores_eth-test.c opencores_eth.c irq.c cpu.c -D_CBMC_\
  -DETHOC_BENCHMARK_PROP_1 -DETHOC_BENCHMARK_PROP_2 \
  -o ethoc_hw_m32_prop1_prop2.gb
$GOTO_INSTRUMENT --count-eloc ethoc_hw_m32_prop1_prop2.gb
$GOTO_CC -m32 opencores_eth-test.c opencores_eth.c irq.c cpu.c -D_CBMC_\
  -DETHOC_BENCHMARK_PROP_1 -DETHOC_BENCHMARK_PROP_3 \
  -o ethoc_hw_m32_prop1_prop3.gb
$GOTO_INSTRUMENT --count-eloc ethoc_hw_m32_prop1_prop3.gb
$GOTO_CC -m32 opencores_eth-test.c opencores_eth.c irq.c cpu.c -D_CBMC_\
  -DETHOC_BENCHMARK_PROP_1 -DETHOC_BENCHMARK_PROP_4 \
  -o ethoc_hw_m32_prop1_prop4.gb
$GOTO_INSTRUMENT --count-eloc ethoc_hw_m32_prop1_prop4.gb

mkdir -p results.cbmc
cd results.cbmc
rm -rf results.txt ethoc-hw.web

cpbm run --cmd $CBMC ../ethoc_hw_m32_prop1_prop2.gb -- \
  --unwind 2 --partial-loops >> results.txt
cpbm run --cmd $CBMC ../ethoc_hw_m32_prop1_prop3.gb -- \
  --unwind 2 --partial-loops >> results.txt
cpbm run --cmd $CBMC ../ethoc_hw_m32_prop1_prop4.gb -- \
  --unwind 2 --partial-loops >> results.txt

cpbm csv cbmc results.txt > results.csv
cpbm web results.csv ethoc-hw.web
chmod -R a+rX ethoc-hw.web

