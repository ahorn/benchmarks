#!/bin/bash

# Absolute path to SMT Kit directory where its README.md file exists
SMTKIT_PREFIX=/path/to/smt-kit

NSE_REWRITE=/path/to/nse-rewrite.sh

# Absolute path to directory that contains a lib/ and include/
# subdirectory with the GMP library and header, respectively
GMP_DIR=/opt/local

export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:${SMTKIT_PREFIX}/solvers/z3/build
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${SMTKIT_PREFIX}/solvers/z3/build

BENCHMARK_FILES="modulus-safe
    modulus-unsafe 
    concrete-sum-safe
    concrete-sum-unsafe 
    bst-safe
    bst-unsafe 
    counter-safe 
    counter-unsafe 
    insertion-sort-safe 
    insertion-sort-unsafe 
    merge-sort-safe 
    merge-sort-unsafe 
    sum-recursive-safe 
    sum-recursive-unsafe"

for f in ${BENCHMARK_FILES}
do
  rm "${f}"*
  cp "../${f}.cpp" .
  ${NSE_REWRITE} "${f}.cpp"
  ./benchmark.sh "${SMTKIT_PREFIX}" "${GMP_DIR}" "${f}"
done
