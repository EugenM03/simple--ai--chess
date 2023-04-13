#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "struct.h"

// Starts a chess game by allocating memory for a 8x8 chess table, and
// initialising official chess starting position
piece_t ***start_game(void)
{
	// We want this in something like start_game_function
	// Allocate memory for the chess table
	piece_t ***table = calloc(8, sizeof(piece_t **));
	for (int i = 0; i < 8 ; i++) {
		table[i] = calloc(8, sizeof(piece_t *));

		if (i == 0 || i == 1 || i == 6 || i == 7)
			for (int j = 0; j < 8; j++)
				table[i][j] = calloc(1, sizeof(piece_t));
	}

	piece_t *pawn = calloc(1, sizeof(piece_t));
	pawn->type = 'p';
	//pawn->move = &move_pawn;

	piece_t *rook = calloc(1, sizeof(piece_t));
	rook->type = 'R';
	//rook->move = &move_rook;

	piece_t *knight = calloc(1, sizeof(piece_t));
	knight->type = 'N';
	//knight->move = &move_knight;

	piece_t *bishop = calloc(1, sizeof(piece_t));
	bishop->type = 'B';
	//bishop->move = &move_bishop;

	piece_t *queen = calloc(1, sizeof(piece_t));
	queen->type = 'Q';
	//queen->move = &move_queen;

	piece_t *king = calloc(1, sizeof(piece_t));
	king->type = 'K';
	//king->move = &move_king;

	int8_t i, j;
	for (i = 1; i < 8; i += 5)
		for (j = 0; j < 7; j++)
			memcpy(table[i][j], pawn, sizeof(piece_t));

	for (i = 0; i < 8; i += 7) { // very noice
		memcpy(table[i][0], rook, sizeof(piece_t));
		memcpy(table[i][7], rook, sizeof(piece_t));

		memcpy(table[i][1], knight, sizeof(piece_t));
		memcpy(table[i][6], knight, sizeof(piece_t));

		memcpy(table[i][2], bishop, sizeof(piece_t));
		memcpy(table[i][5], bishop, sizeof(piece_t));

		memcpy(table[i][3], queen, sizeof(piece_t));
		memcpy(table[i][4], king, sizeof(piece_t));
	}

	for (j = 0; j < 8; j++) {
		table[0][j]->type *= -1;
		table[1][j]->type *= -1;
	}

	return table;
}
