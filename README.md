# CppND-Capstone (SDLBlackjack)
A blackjack program written as Capstone project for the C++ Nanodegree program
on Udacity.

## Build instructions
The project uses the CMake build system and should be easy to build. After
cloning the repository to a location of your choice, the following four
commands should build it:
```
mkdir build
cd build
cmake ..
make
```

## Description
The project enables you to play hands of blackjack against a dealer. Using either
the mouse or keyboard, hit or stand to get as close to 21 without going over.
The dealer plays next until they reach 17 or greater (or bust). The game will then
inform you if you've won, lost or tied, at which point you can choose to quit or
play another hand.

Admittedly, it's a basic game of blackjack, with no betting, doubling down or
splitting. I decided to keep it no frills for the project since it was a first
C++ project as well as graphical program and I didn't want to bite off too much.
I'll expand on the program in the future as my skills develop.

### File Structure
```
CppND-Capstone
|
+-- cmake
|   |
|   +-- FindSDL2_image.cmake
|
+-- res
|   |
|   +-- (BMP files used for textures)
|
+-- src
|   |
|   +-- res
|   |   |
|   |   +-- (.xcf files from GIMP: original texture files)
|   |
|   +-- CMakeLists.txt
|   |
|   +-- Card.cpp
|   |
|   +-- Card.h
|   |
|   +-- Controller.cpp
|   |
|   +-- Controller.h
|   |
|   +-- DeckOfCards.cpp
|   |
|   +-- DeckOfCards.h
|   |
|   +-- Renderer.cpp
|   |
|   +-- Renderer.h
|   |
|   +-- main.cpp
|
+-- CMakeLists.txt
|
+-- LICENSE
|
+-- README.md
```

## Rubrics addressed
* The project demonstrates an understanding of C++ functions and control structures.
  - range based for loop
    - DeckOfCards::ScoreHand (line 127)
  - for loop
    - DeckOfCards::Shuffle (line 57)
    - DeckOfCards::CreateShoe (line 85)
  - if/else
    - DeckOfCards::ScoreHand (lines 128-138) - nested if(if/else)/else
    - Controller::WhoWon (lines 267) - if/else/else/else/else
  - switch
    - Controller::GameLoop (lines 82-92)
    - Controller::PlayPlayerHand (lines 175-184)
  - while loop
    - Controller::GameLoop (lines 45, 73, 75)
* The project accepts user input and processes the input.
  - Controller::GameLoop (lines 75-109 & 171-211)
    - Accepts either keyboard or mouse input to get a choice from the user
* The project reads data from a file and process the data, or the program writes
 data to a file.
  - Renderer::LoadTexture (line 189)
  - Card::Card (lines 37 & 42)
* The project uses Object Oriented Programming techniques.
  - main creates two objects:
    - Renderer object with 4 class methods
    - Controller object with 7 class methods
  - Controller creates a DeckOfCards object with 4 class methods
  - DeckOfCards creates an array of Card objects with 3 class methods
* Classes use appropriate access specifiers for class members.
  - Renderer:
    - Public: window and renderer for outside class access
    - Private: window_width and window_height
  - Card:
    - Private: card, rank, suit - all with getters to allow access to their
      values
  - DeckOfCards:
    - Public: shoe - need direct access to the array
    - Private: shuffle, reshuffle, card_to_deal - all internal tracking variables
  - Controller:
    - Private: deck, player, dealer - all internal though passed as parameters to
        external methods
* Class constructors utilize member initialization lists.
  - Renderer, Card