#!/usr/bin/env bash

rm halite_bot.zip &> /dev/null
zip -r halite_bot.zip ./hlt *.cpp *.hpp MyBot.cpp