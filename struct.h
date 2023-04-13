#pragma once

#include <stdbool.h>
#include <inttypes.h>

typedef struct piece_t {
	// uint8_t color;  // piece's color
	int8_t type;   // piece's type

	// Pointer to a function that checks if the piece can move to the given
	// position and returns TRUE if it can. Otherwise, returns FALSE
	bool (*move)(struct piece_t ***, uint8_t[2], uint8_t[2]);
} piece_t;

typedef struct game_state_t {
	struct piece_t ***table;
	bool ai_mode; // If AI mode is selected on START_GAME AI
	bool turn; // If it's white's (default, true) or black's (false) turn

} game_state_t;
