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

void strlwr(char *str)
{
	for (size_t i = 0; i < strlen(str); i++)
		str[i] = tolower(str[i]);
}

char cmd_selection(char *command)
{
	// for finding the case we're currently in, we use *valid
	// char *valid;
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

	// valid = strstr(command, "HELP");
	// if (valid && !strcmp(valid, "HELP"))
	// 	cmd_letter = 'H';

	// valid = strstr(command, "START_GAME");
	// if (valid && !strcmp(valid, command))
	// 	cmd_letter = 'S';

	// valid = strstr(command, "EXIT");
	// if (valid && !strcmp(valid, "EXIT")) {
	// 	if (1) // maybe an if here?
	// 		cmd_letter = '1';
	// 	else
	// 		cmd_letter = '0';
	// }

	return cmd_letter;
}

int main(void)
{
	// Commands from STDIN will be stored in *command

	// piece_t ***table = NULL;
	// bool ai_mode = false;
	game_state_t *state = calloc(1, sizeof(game_state_t));
	state->ai_mode = false;
	state->table = NULL;

	char *command = calloc(MAX_CMD_SIZE, sizeof(char));
	while (1) {
		scanf("%s", command);
		if (!command)
			continue;

		// Depending on the commands given, we run
		// the correspondent command

		switch (cmd_selection(command)) {
		case 'H': {
			// help_game_function();
			break;
		}
		case 'G': {
			command[0] = '\0';
			scanf("%[^\n]", command); // Problem with START_GAME AI
			if (strcmp(command, "") == 0) {
				state->ai_mode = false;
			} else {
				if (strcmp(command, "AI") == 0) {
					state->ai_mode = true;
					printf("What color do you wish to play as? (W / b): ");
					while (1) {
						command[0] = '\0';
						scanf("%[^\n]", command);
						strlwr(command);
						if (strcmp(command, "") == 0 || strcmp(command, "w") == 0 || strcmp(command, "white") == 0) {
							state->turn = true;
							break;
						} else {
							if (strcmp(command, "b") == 0 || strcmp(command, "black") == 0) {
								state->turn = false;
								break;
							}
						}
						puts("Invalid command. Please input w/b");
					}
				} else {
					puts("Invalid command. Please try again.");
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
					break;
				} else {
					if (strcmp(command, "y") == 0 || strcmp(command, "yes") == 0) {
						// save_game();
						break;
					}
				}
				puts("Invalid command. Please input y/n.");
			}
			// deallocate_table();
			state->table = start_game();
			if (state->turn == false) {
				state->turn = true;
				// move_ai();
			}
			break;
		}
		case 'S': {
			// save_game_function();
			break;
		}
		case 'L': {
			// load_game_function();
			break;
		}
		case '0': {
			// save_game_function();
			// dealloc_table();
			return 0;
		}
		case 'M': {
			// move_player();
			// if (state->ai_mode)
			//		move_ai();
			break;
		}
		case 'P': {
			// skip_turn();
			break;
		}
		case 'R': {
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
