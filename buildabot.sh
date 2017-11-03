#!/usr/bin/env bash

ROOT=$(git rev-parse --show-toplevel)
mkdir "${ROOT}/build" &>/dev/null
pushd ${ROOT}/build &>/dev/null

cmake .. && make clean MyBot
ERR=$?

popd

exit ${ERR}