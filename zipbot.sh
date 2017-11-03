#!/usr/bin/env bash

ROOT=$(git rev-parse --show-toplevel)
pushd ${ROOT} &>/dev/null

rm bot.zip &> /dev/null
zip -rq bot.zip ./hlt ./bot MyBot.cpp
ERR=$?

popd
exit ${ERR}

