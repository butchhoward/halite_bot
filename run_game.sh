#!/usr/bin/env bash
set -e

ROOT="$(git rev-parse --show-toplevel)/bots"

#TODO: get 4 most recent bots as defaults
DEFAULT_BOT="MyBot_1.0.10"

BOT1="${ROOT}/${1:-${DEFAULT_BOT}}"
BOT2="${ROOT}/${2:-${DEFAULT_BOT}}"
BOT3="${ROOT}/${3:-${DEFAULT_BOT}}"
BOT4="${ROOT}/${4:-${DEFAULT_BOT}}"

echo "=====" > t.out
../halite -d "240 160" "${BOT1}" "${BOT2}" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" > t.out
../halite -d "240 160" "${BOT1}" "${BOT3}" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" > t.out
../halite -d "240 160" "${BOT1}" "${BOT4}" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" >> t.out
../halite -d "360 240" "${BOT1}" "${BOT2}" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" >> t.out
../halite -d "360 240" "${BOT1}" "${BOT3}" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" >> t.out
../halite -d "360 240" "${BOT1}" "${BOT4}" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" >> t.out
../halite -d "240 160" "${BOT1}" "${BOT2}" "${BOT3}" "${BOT4}" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" >> t.out
../halite -d "384 256" "${BOT1}" "${BOT2}" "${BOT3}" "${BOT4}" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" >> t.out
../halite -d "288 192" "${BOT1}" "${BOT2}" "${BOT3}" "${BOT4}" | tee /dev/tty | grep -v '^Turn' >> t.out

mv *.log ./Replays/

echo "======Results======="
grep 'rank #1' t.out | tee t_results.out
