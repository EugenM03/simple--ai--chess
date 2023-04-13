#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "struct.h"

piece *** start_game(bool ai)
{
    // We want this in something like start_game_function
	// Allocate memory for the chess table
	piece ***table = calloc(8, sizeof(piece **));
	for (int i = 0; i < 8 ; i++) {
		table[i] = calloc(8, sizeof(piece *));

		if (i == 0 || i == 1 || i == 6 || i == 7)
			for (int j = 0; j < 8; j++)
				table[i][j] = calloc(1 , sizeof(piece));
	}
    (void)ai;

    return table;
}