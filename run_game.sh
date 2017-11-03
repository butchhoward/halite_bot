#!/usr/bin/env bash
set -e

ROOT="$(git rev-parse --show-toplevel)/bots"

#TODO: get 4 most recent bots as defaults

BOT1="${ROOT}/${1:-MyBot_1.0.3}"
BOT2="${ROOT}/${2:-MyBot_1.0.3}"
BOT3="${ROOT}/${3:-MyBot_1.0.3}"
BOT4="${ROOT}/${4:-MyBot_1.0.3}"

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
