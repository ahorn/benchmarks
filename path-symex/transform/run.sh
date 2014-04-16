#!/bin/bash

SMTKIT_PREFIX=

./benchmark.sh "${SMTKIT_PREFIX}" "modulus-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "modulus-unsafe"
./benchmark.sh "${SMTKIT_PREFIX}" "concrete-sum-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "concrete-sum-unsafe"
./benchmark.sh "${SMTKIT_PREFIX}" "bst-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "bst-unsafe"
./benchmark.sh "${SMTKIT_PREFIX}" "counter-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "counter-unsafe"
./benchmark.sh "${SMTKIT_PREFIX}" "insertion-sort-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "insertion-sort-unsafe"
./benchmark.sh "${SMTKIT_PREFIX}" "merge-sort-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "merge-sort-unsafe"
./benchmark.sh "${SMTKIT_PREFIX}" "sum-recursive-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "sum-recursive-unsafe"
