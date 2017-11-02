#!/usr/bin/env bash
set -e

rm *.hlt
rm t.out
echo "=====" > t.out
../halite -d "240 160" "./MyBot" "./MyBot" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" >> t.out
../halite -d "264 176" "./MyBot" "./MyBot" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" >> t.out
../halite -d "360 240" "./MyBot" "./MyBot" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" >> t.out
../halite -d "240 160" "./MyBot" "./MyBot" "./MyBot" "./MyBot" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" >> t.out
../halite -d "384 256" "./MyBot" "./MyBot" "./MyBot" "./MyBot" | tee /dev/tty | grep -v '^Turn' >> t.out

echo "=====" >> t.out
../halite -d "288 192" "./MyBot" "./MyBot" "./MyBot" "./MyBot" | tee /dev/tty | grep -v '^Turn' >> t.out
