# CPPND: Capstone Snake Game Example

This is a working repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

# Project Description

1. The game can be played upto level 5. Level 5 is the final level.
2. Each level has its different map. Level 1 doesn't have any obstacles. Further levels have the obstacles.
3. If the snake collides with any obstacle. Game ends.
4. If the size of the snake crosses 10, then the level Changes and the size of the snake is reset but score keeps increasing.
 # Enjoy Playing the game.
 
# Some Future improveents:

1. Scoreboard and a startscreen can be added.
2. Number of snake life can be increased.
3. When snake dies; some audio sound can be added and the window can close itself.
4. There can be start stop button to start and pause the game in between. There can be time delay given when level changes.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.
