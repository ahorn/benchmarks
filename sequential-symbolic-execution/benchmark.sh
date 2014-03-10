#!/bin/bash

SYMEX=./symex

# Assumes the file uses a constant N
FILENAME=$1
N_STEP=${2:-5}
N_MAX=${3:-20}

usage() {
  echo "Usage: $0 file.c [step=5] [max=20]"
  exit 1
}

error() {
  echo "$@" 1>&2
  exit 1
}

run() {
  for ((N=${N_STEP}; N<=${N_MAX}; N+=${N_STEP})) do
    local timestamp=$(date +"%Y-%m-%d-%H-%M")
    local log="${FILENAME}.${N}.${timestamp}.log"
    $SYMEX ${FILENAME} -D N=${N} 2>&1 > ${log}
  done
}

# invoke usage when necessary
[[ $# -eq 0 ]] && usage

if ! [[ -f "${FILENAME}" ]]; then
  error "Cannot find ${FILENAME}"
else
  run
fi
