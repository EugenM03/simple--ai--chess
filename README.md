&copy; Lazar Cristian-Stefan (314CA) and Munteanu Eugen (315CA) -- 2023-2024

# BlitzBolt - a simple Chess game (written only in C!)

## Introduction

BlitzBolt is a command-line based chess game written in C language (only!), designed for players who want to enjoy a quick game of chess on their computer. It is a simple yet fun game that you can play against an AI or with another player.

The game features a standard 8x8 chess board, with pieces that move according to the standard chess rules. The environment where all the action is happening (sadly enough) is the console command you are currently running the game. The game also features a basic AI opponent, which provides a (somewhat) good challenge for beginners and casual players.

---
&nbsp;

## Usage

To create the program, use the command 'make' (or any equivalent for this Ubuntu command).  Upon opening the executable, you can choose if you want to play versus another player (option 1) or play against our *(Stockfish's baby)* AI.\
\
After that, an implementation of a chess table will be shown to `STDOUT`. By default, you are playing as white and thus making the first move (implementation of color choice might not be available in the final release).

### How are moves supposed to be made?

To make a move, the syntax is as it follows:\
*\[column_initial_position\]\[number_initial_position]-\[column_final_position\]\[number_final_position\]*

For instance, to start King's Pawn Opening (pawn to e4), you just type: d4-e4.\
**Note:** no pieces need to be mentioned, detection and validation of moves may be done in the final release.

---
&nbsp;

## Implementation

All pieces are dynamically alocated in memory and stored as a structure:
```C
typedef struct piece {
  char color;  // piece's color
  char type;   // piece's type

  // Pointer to a function that checks if the piece can move to the given
  // position and returns TRUE if it can. Otherwise, returns FALSE
  bool (*move)(piece ***, uint8_t[2], uint8_t[2]);
} piece;
```

---
&nbsp;

## Alpha-Beta Pruning

Chess is a complex game with many possible moves and positions. When searching for the best move in a given position, it's important to use an efficient search algorithm that can explore the game tree as quickly as possible. Alpha-Beta Pruning is a popular algorithm for this purpose, as it can significantly reduce the number of nodes that need to be searched. \
Implementation of chess AI may use Alpha-Beta Prunning in the final release.

---
&nbsp;

## Final Words

Whether you're a seasoned chess player or a beginner looking to learn chess (*currently population for Chess: everyone*), BlitzBolt is the perfect way to get your fix. So why not give it a try today?
