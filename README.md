# halite_bot
Playing with halite

# Goals

1. Make a halite bot in C++
1. Brush up on my C++ (especially the new things)
1. Explore some machine learning (maybe)

I got a bot built, packaged, and sumbitted using the default C++ starter kit. There were a few things I had to modify to get it going. The intial starter kit appeared to be very Windows-y, Visual Studio 2017 focused. 

The local-runner for halite is not well documented. There seems to be plenty of help in the [Halite Forums](https://forums.halite.io). I decided to settle on the convention that it will be one directory level up from the current folder.

# Lessons

* You must send something to send_moves() every turn (or at least with in every 2-second period) even if it is an empty list of moves else the game will timeout.

* Ship IDs are stable across turns. 

* C++ 11 has lambdas.

* Even though the C++ starter kit is based on CMake, CMake is not used on the game server. A simple script is used to compile the code. Source in subdirectories will be found and compiled (it basically scans all the folders in the zip archive for .cpp and .hpp file and compiles them). There is not, however, any way to pass compiler options. This means that you cannot set include paths and must use relative paths in all includes to other folders. Not a huge deal, but a thing to keep in mind.

# Todo

* Route to the nearest planet first instead of iterating the planet list in index order

* If the ship passes near a planet that is dockable on its way to the selected destination, then dock there.

* Go fast as much as possible. Slow only for docking (the default navigation function appears to do this fairly well).

* Figure out why the ships get into a state where the just stop moving. They should always be docking or attacking.

* Find a way to attack other ships instead of just attacking planets.

# Scripts

`tagabot.sh`

Tags the current git repository with a version tag updated to one patch version greater than the most recent tag.

Builds the bot code using `buildabot.sh`. The bot file is renamed using the current tag. The bot file is stored in the `./bots` folder.

Creates the bot zip file using the `zipbot.sh` scripts. The zip archive is renamed using the current tag. The zip file is stored in the `./bots` folder.


`buildabot.sh`

Compile the current code into a bot.

Compiling is done in the `./build` folder. 

`zipbot.sh`

Package the current bot into a zip ready for submission to the halite server.

Creates a file named `./bot.zip`.


`run_game.sh`

Run a local-runner game playing the current bot against the previous version in several scenarios.

```bash
./run_game.sh [MyBot_1.0.4] [...]
```

Arguments are the bot names to compete (just the file name). 

The bots must exist in the `./bots` folder.

If bot arguments are not given the defaults will be used (Currently MyBot_1.0.3). Eventually it will grab the most recent 4 bots and play them, but not yet.


## Helpful Command Lines

**Build and run**

`rm *.log; clear; make clean MyBot && ./run_game.sh`


**Build and run with fresh CMake run included**
`rm *.log; clear; ./buildabot.sh  && ./run_game.sh`



