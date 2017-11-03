#!/usr/bin/env bash

rm halite_bot.zip &> /dev/null
zip -r bot.zip ./hlt ./bot MyBot.cpp
