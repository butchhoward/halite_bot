#!/usr/bin/env bash
set -e

ROOT="$(git rev-parse --show-toplevel)/bots"

function get_default_bot()
{
    #get highest tag number
    local VERSION=`git describe --abbrev=0 --tags 2>/dev/null`
    local VERSION_BITS=(${VERSION//./ })
    local VNUM1=${VERSION_BITS[0]}
    local VNUM2=${VERSION_BITS[1]}
    local VNUM3=${VERSION_BITS[2]}

    #use the previous as the default
    local VNUM3=$((VNUM3-1))

    echo "$VNUM1.$VNUM2.$VNUM3"
}

#TODO: get 4 most recent bots as defaults
# DEFAULT_BOT="MyBot_1.0.10"
DEFAULT_BOT=$(get_default_bot)

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
