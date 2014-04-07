#!/bin/bash

UNSAFE_STATUS=10

TOOL=./symex
CHRONO="/usr/bin/time"

# Assumes the file uses a constant N
FILENAME=$1
N_STEP=${2:-5}
N_MAX=${3:-20}

machine_info=""

usage() {
  echo "Usage: $0 file.c [step=5] [max=20]"
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

run() {
  which $TOOL > /dev/null || error "$TOOL is not an executable"

  for ((N=${N_STEP}; N<=${N_MAX}; N+=${N_STEP})) do
    local timestamp=$(date +"%Y-%m-%d-%H-%M")
    local log="${FILENAME}.${N}.${timestamp}.log"
    local result="safe"

    ${CHRONO} ${TOOL} ${FILENAME} -D N=${N} 2>&1 > ${log}
    if [[ $? -eq UNSAFE_STATUS ]] ; then
      result="unsafe"
    fi

    echo "------------ Benchmark ------------" >> ${log}
    echo "Program is ${result} [${FILENAME}]" >> ${log}
  done
}

# basic checks
[ -n "$TOOL" ] || error "Please set software verification tool"
[[ $# -eq 0 ]] && usage
check_platform

if ! [[ -f "${FILENAME}" ]]; then
  error "Cannot find ${FILENAME}"
else
  run
fi
