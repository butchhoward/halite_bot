# halite_bot
Playing with halite

# Goals:

1. Make a halite bot in C++
1. Brush up on my C++ (especially the new things)
1. Explore some machine learning (maybe)

I got a bot built, packaged, and sumbitted using the default C++ starter kit. There were a few things I had to modify to get it going. The intial starter kit appeared to be very Windows-y, Visual Studio 2017 focused. 

The local-runner for halite is not well documented. I decided to settle on the convention that it will be one directory level up from the current folder.

# Scripts

`buildabot.sh`
Compile the current code into a bot.

`run_game.sh`

Run a local-runner game playing the current bot against itself.

`zipbot.sh`

Package the current bot into a zip ready for submission to the halite server.

## Helpful Command Lines

**Build and run**

`rm *.log; clear; make clean MyBot && ./run_game.sh`


**Build and run with fresh CMake run included**
`rm *.log; clear; ./buildabot.sh  && ./run_game.sh`



