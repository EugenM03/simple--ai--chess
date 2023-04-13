#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"
#include "bulk.h"

#define MAX_CMD_SIZE 128
#define COMMAND_INTERPRETER(cmd_string, cmd_comp_string, cmd_ret_value) \
	do { \
		if (strcmp(cmd_string, cmd_comp_string) == 0) \
			cmd_letter = cmd_ret_value; \
	} while (0)

// Convert a given string (char *) to lowercase
void strlwr(char *str)
{
	for (size_t i = 0; i < strlen(str); i++)
		str[i] = tolower(str[i]);
}

// Attribute for each command a specific character (letter)
char cmd_selection(char *command)
{
	char cmd_letter = '-';

	COMMAND_INTERPRETER(command, "HELP", 'H');
	COMMAND_INTERPRETER(command, "START_GAME", 'G');
	COMMAND_INTERPRETER(command, "SAVE", 'S');
	COMMAND_INTERPRETER(command, "LOAD", 'L');
	COMMAND_INTERPRETER(command, "EXIT", '0');
	COMMAND_INTERPRETER(command, "MOVE", 'M');
	COMMAND_INTERPRETER(command, "PASS", 'P');
	COMMAND_INTERPRETER(command, "RESIGN", 'R');
	COMMAND_INTERPRETER(command, "HINT", 'D');

	return cmd_letter;
}

int main(void)
{
	// piece_t ***table = NULL;
	// bool ai_mode = false;

	// Initialising variables used throughout the game:

	// state - the current state of the game: stores table,
	// if the game is played versus an AI, and current player's turn)
	game_state_t *state = calloc(1, sizeof(game_state_t));
	state->ai_mode = false;
	state->table = NULL;

	// Commands from STDIN will be stored in *command
	char *command = calloc(MAX_CMD_SIZE, sizeof(char));

	while (1) {
		scanf("%s", command);
		if (!command)
			continue;

		// Depending on the commands given, we run
		// the correspondent command
		switch (cmd_selection(command)) {
		case 'H': { // HELP
			// help_game_function();
			break;
		}

		// Programul pare ok pentru START_GAME [AI], in afara faptului cand
		// dai enter (\n) pur si simplu de multe ori (pentru cazul default)

		case 'G': { // START_GAME [AI]
			scanf("%[^\n]", command); // Problem with START_GAME AI (" AI" instead of "AI")
			if (strcmp(command, "START_GAME") == 0) {
				state->ai_mode = false;
				printf("Output: %s\n", command);
			} else {
				if (strcmp(command, " AI") == 0) {
					state->ai_mode = true;
					printf("What color do you wish to play as? (W / b): ");
					while (1) {
						command[0] = '\0';
						scanf("\n%[^\n]", command);
						strlwr(command);
						if (strcmp(command, "") == 0 || strcmp(command, "w") == 0 || strcmp(command, "white") == 0) {
							printf("Your color: white\n");
							state->turn = true;
							break;
						}
						if (strcmp(command, "b") == 0 || strcmp(command, "black") == 0) {
							printf("Your color: black\n");
							state->turn = false;
							break;
						}
						printf("Invalid command. Please input w/b: ");
					}
				} else {
					printf("Invalid command. Please try again.\n");
					break;
				}
			}

			if (!state->table) {
				state->table = start_game();
				if (!state->turn) {
					state->turn ^= 1;
					// move_ai(); state->turn = false in function
				}
				break;
			}

			printf("Do you want to save the current game? (y / N): ");

			while (1) {
				scanf("\n%[^\n]", command);
				strlwr(command);
				if (strcmp(command, "") == 0 || strcmp(command, "n") == 0 ||
					strcmp(command, "no") == 0) {
					printf("Saving? No\n");
					break;
				}
				if (strcmp(command, "y") == 0 || strcmp(command, "yes") == 0) {
					printf("Saving? Yes\n");
					// save_game();
					break;
				}
				printf("Invalid command. Please input y/n: ");
			}

			// deallocate_table();
			state->table = start_game();
			if (!state->turn) {
				state->turn = true;
				// move_ai();
			}
			break;
		}
		case 'S': { // SAVE <path_to_file>
			// save_game_function();
			break;
		}
		case 'L': { // LOAD <path_to_file>
			// load_game_function();
			break;
		}
		case '0': { // EXIT
			// save_game_function(); - "Do you want to save the current game?"
			// dealloc_table();
			return 0;
		}
		case 'M': { // MOVE (eg. d4-e4)
			// move_player();
			// if (state->ai_mode)
			//		move_ai();
			break;
		}
		case 'P': { // PASS
			// skip_turn(); - Too much tension? Take a break; (lol)
			break;
		}
		case 'R': { // RESIGN
			// dealloc_table();
			break;
		}
		default: {
			printf("Invalid command.\n");
			break;
		}
		}
	}

	if (command) {
		free(command);
		command = NULL;
	}
	// d4-e4
	// 8
	// 7
	// 6
	// 5
	// 4
	// 3
	// 2
	// 1 a b c d e f g h
	// Testing screen clear
	for (int i = 0; i < 21; i++)
		printf("weiqwjeioquoiqweoquqw%d\n", i);
	int d;
	scanf("%d", &d);
	if (d == 1)
		printf("\033[10;H\033[J");
	return 0;
}
