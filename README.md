# Benchmarks

This repository contains benchmarks for formal co-validation of hardware and
low-level software interfaces. The source code for these benchmarks was
extracted from QEMU and Linux.

## RTC Benchmark

The __RTC__ benchmark illustrates the hardware/software interface for a
real-time clock. The focus is on Register B and the ten time/calendar and alarm
bytes:

![RTC Registers][rtc-registers]

Courtesy of [MC146818 data sheet][rtc-datasheet]

To run the experiments on the HW/SW model, execute the following command from
within the folder `sw-hw/linux/rtc\_x86`: 

    $ ./run\_expt.sh [Num of Runs] [Experiment Name] [Property No. (1 to 11)]

Use the same command in the folder `qemu-hw/rtc` to run the experiments on the
standalone HW model.

To get the total runtime and runtime spent on the decision procedure, run
the command:

    $ ./get\_result.sh [Experiment Name]

## I2C Benchmark

The __I2C__ benchmark illustrates hardware/software interface for a temperature
sensor on a serial bus. Thus, this benchmark goes beyond fixed-sized register
updates as illustrated by the following waveform:

![TMP105 I2C Write Word Protocol][tmp105-i2c-word-write]

Courtesy of [TMP105 data sheet][tmp105-datasheet]

To run the experiments on the HW/SW model, execute the following command
from within the folder `sw-hw/linux/tmp105\_x86`:

    $ ./run\_expt.sh [Num of Runs] [Experiment Name] [Property No. (1 to 21)]

Use the same command in folder `qemu-hw/tmp105` to run experiments on the
standalone HW model.

To get the total runtime and runtime spent on the decision procedure, run
the command:

    $ ./get\_result.sh [Experiment Name]

## ETHOC Benchmark

The __ETHOC__ benchmark exemplifies a known concurrency bug in a NAPI-enabled
driver for an Ethernet MAC.

Summary tables and full log files of these experiments are available at
[ethoc-hw] for the hardware model, and [ethoc-sw-hw] for the combined
hardware+software implementation. These tables and results were generated using
our [benchmarking framework][cpbm]. The corresponding commands are documented in
the scripts [ethoc-hw-experiments] and [ethoc-sw-hw-experiments], which were
used to compute and generate all these results.

## Contribute Benchmarks

We welcome contributions of new benchmarks. See also our [Wiki][wiki] for
useful resources.

[rtc-registers]: https://raw.github.com/ahorn/benchmarks/master/doc/rtc/rtc_registers.jpg
[rtc-datasheet]: http://www.freescale.com/files/microcontrollers/doc/data_sheet/MC146818.pdf
[tmp105-datasheet]: http://www.ti.com/lit/ds/symlink/tmp105.pdf
[tmp105-i2c-word-write]: https://raw.github.com/ahorn/benchmarks/master/doc/i2c/tmp105-i2c-word-write.jpg
[ethoc-hw]: http://htmlpreview.github.com/?https://github.com/ahorn/benchmarks/master/doc/ethoc/ethoc-hw.web/index.html
[ethoc-sw-hw]: http://htmlpreview.github.com/?https://github.com/ahorn/benchmarks/master/doc/ethoc/ethoc-sw-hw.web/index.html
[ethoc-hw-experiments]: https://github.com/ahorn/benchmarks/blob/master/qemu-hw/ethoc/experiments.sh
[ethoc-sw-hw-experiments]: https://github.com/ahorn/benchmarks/blob/master/sw-hw/linux/ethoc/experiments.sh
[cpbm]: http://www.cprover.org/software/benchmarks/
[wiki]: https://github.com/ahorn/benchmarks/wiki/_pages
