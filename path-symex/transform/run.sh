#!/bin/bash

SMTKIT_PREFIX=/nas/ahorn/2014/smt-kit
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/nas/ahorn/2014/smt-kit/solvers/z3/build:/nas/ahorn/2014/smt-kit/target/lib

rm modulus-safe \
   concrete-sum-safe \
   modulus-unsafe \
   concrete-sum-unsafe \
   bst-safe bst-unsafe \
   counter-safe \
   counter-unsafe \
   insertion-sort-safe \
   insertion-sort-unsafe \
   merge-sort-safe \
   merge-sort-unsafe \
   sum-recursive-safe \
   sum-recursive-unsafe

./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "modulus-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "modulus-unsafe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "concrete-sum-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "concrete-sum-unsafe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "bst-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "bst-unsafe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "counter-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "counter-unsafe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "insertion-sort-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "insertion-sort-unsafe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "merge-sort-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "merge-sort-unsafe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "sum-recursive-safe"
./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "sum-recursive-unsafe"
