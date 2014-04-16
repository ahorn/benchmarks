#!/bin/bash

SMTKIT_PREFIX=

./run.sh ${SMTKIT_PREFIX} modulus-safe
./run.sh ${SMTKIT_PREFIX} modulus-unsafe
./run.sh ${SMTKIT_PREFIX} concrete-sum-safe
./run.sh ${SMTKIT_PREFIX} concrete-sum-unsafe
./run.sh ${SMTKIT_PREFIX} bst-safe
./run.sh ${SMTKIT_PREFIX} bst-unsafe
./run.sh ${SMTKIT_PREFIX} counter-safe
./run.sh ${SMTKIT_PREFIX} counter-unsafe
./run.sh ${SMTKIT_PREFIX} insertion-sort-safe
./run.sh ${SMTKIT_PREFIX} insertion-sort-unsafe
./run.sh ${SMTKIT_PREFIX} merge-sort-safe
./run.sh ${SMTKIT_PREFIX} merge-sort-unsafe
./run.sh ${SMTKIT_PREFIX} sum-recursive-safe
./run.sh ${SMTKIT_PREFIX} sum-recursive-unsafe
