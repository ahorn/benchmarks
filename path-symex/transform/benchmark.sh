#!/bin/bash

CXX="clang++"
CHRONO="/usr/bin/time"

SMTKIT_PREFIX=$1
BENCHMARK=$2

usage() {
  echo "Usage: $0 smt-kit-prefix benchmark"
  exit 1
}

error() {
  echo "$@" 1>&2
  exit 1
}

check_platform() {
  case `uname -s` in
    Darwin|Linux|CYGWIN_*)
      ;;
    *)
      error "Unsupported platform `uname -s`"
      ;;
  esac
}

# Total runtime of compilation and symbolic execution
run() {
  ${CHRONO} sh -c "echo ${BENCHMARK}; ${CXX} -std=c++11 -I${SMTKIT_PREFIX}/include -L${SMTKIT_PREFIX}/target/lib -I${SMTKIT_PREFIX}/solvers/z3/src/api/c++ -I${SMTKIT_PREFIX}/solvers/z3/src/api -L${SMTKIT_PREFIX}/solvers/z3/build -lz3 -lsmt -o ${BENCHMARK} "${BENCHMARK}.cpp"; ./${BENCHMARK}"
}

# basic checks
[[ $# -eq 0 ]] && usage

[ -n "$SMTKIT_PREFIX" ] || error "Please specify SMT Kit prefix"
[ -n "$BENCHMARK" ] || error "Please specify benchmark name"
check_platform

if ! [[ -f "${BENCHMARK}.cpp" ]]; then
  error "Cannot find ${BENCHMARK}.cpp"
else
  run
fi
