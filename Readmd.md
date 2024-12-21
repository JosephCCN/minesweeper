# Minesweeper Game

## What is Minesweeper Game
This is a platform for algorithm competition with minesweeper.
Contestant will design and implement a strategy to play minesweeper.
Contestant only need to implement the `Player::move` function inside `player.cpp`, the game engine and the judge will automatically run the strategy and give verdict.

### Game Play
When the game start, some **BOMB** is placed into a `width * height` grid. `Player` mission is to find all the **BOMB** in minimum number of move.

For each round, `Player::move` is called and it must choose an unchosen grid and *click* on it,
if the *clicked* grid is a **BOMB**, the game ends immediately and considered a loss, 
*OR*
it can put a flag on a grid indicate that it's a **BOMB**(we call it *flag* a **BOMB**), the game is considered a win if all **BOMB** is flagged.

The game will end and considered a **loss** if any one of the below happened:
- A **BOMB** is chosen (not flag a **BOMB**)
- A grid is chosen twice
- A flagged grid is chosen
- A move spend more than 1 second
- The chosen grid is out of bound

The game will end and considered a **win** if and only if:
- All **BOMB** is flagged

## Technical Information
### Enviornment
- C++11 (g++11.4 is used during development)
- Any Linux Distro

### Implement
You **MUST ONLY** do all your work in `player.cpp`, and **DO NOT** change anything in other file, otherwise it may lead to unknown errors.

### Compile
You may use `make` to compile the code into `run` executable file
*OR*
You may use `build.sh` to compile the code into `run` executable file
Using `make` is preferred here

### Run
`./run {metafile path}`
The executable `run` will run and give primary verdict to player actions

### Metafile
One metafile represent the setting of a **single** game, the format is
```
{board width} {board height}
{bomb_1_x} {bomb_1_y}
{bomb_2_x} {bomb_2_y}
.
.
.
```
Please strictly follow the file format, otherwise may lead to unknown exception