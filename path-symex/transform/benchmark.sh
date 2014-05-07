#!/bin/bash

CXX="clang++"

SMTKIT_PREFIX=$1
GMP_DIR=$2
BENCHMARK=$3

usage() {
  echo "Usage: $0 /path/to/smt-kit /path/to/gmp benchmark"
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
  time sh -c "echo ${BENCHMARK}; ${CXX} -std=c++11 -I${SMTKIT_PREFIX}/include -L${SMTKIT_PREFIX}/target/lib -lsmt -I${SMTKIT_PREFIX}/solvers/z3/src/api/c++ -I${SMTKIT_PREFIX}/solvers/z3/src/api -L${SMTKIT_PREFIX}/solvers/z3/build -lz3 -I${SMTKIT_PREFIX}/solvers/msat/include -L${SMTKIT_PREFIX}/solvers/msat/lib -lmathsat -I$GMP_DIR/include -L${GMP_DIR}/lib -lgmp -lgmpxx -I${SMTKIT_PREFIX}/solvers/stp/build/include -L${SMTKIT_PREFIX}/solvers/stp/build/lib -lstp -o ${BENCHMARK} "${BENCHMARK}.cpp"; ./${BENCHMARK}"
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
