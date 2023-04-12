#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "struct.h"

#define MAX_CMD_SIZE 128

char cmd_selection(char *command)
{
	// for finding the case we're currently in, we use *valid
	char *valid;
	char cmd_letter = '-';

	valid = strstr(command, "HELP");
	if (valid && !strcmp(valid, "HELP"))
		cmd_letter = 'H';

	valid = strstr(command, "START_GAME");
	if (valid && !strcmp(valid, command))
		cmd_letter = 'S';

	valid = strstr(command, "EXIT");
	if (valid && !strcmp(valid, "EXIT")) {
		if (1) // maybe an if here?
			cmd_letter = '1';
		else
			cmd_letter = '0';
	}

	return cmd_letter;
}

int main(void)
{
	// Commands from STDIN will be stored in *command

	char *command = calloc(MAX_CMD_SIZE, sizeof(char));

	int run = 1;
	while (run) {
		scanf("%s", command); getchar();

		// Depending on the commands given, we run
		// the correspondent command
		char cmd = cmd_selection(command);
		switch (cmd) {
		case 'H': {
			// help_game_function();
			break;
		}
		case 'S': {
			// save_game_function();
			break;
		}
		case '1': {
			// save_game_function();
			run = 0;
			break;
		}

		default: {
			printf("Invalid command.\n");
			break;
		}

		}
	}

	// We want this in something like start_game_function
	// Allocate memory for the chess table
	piece ***table = calloc(8, sizeof(piece **));
	for (int i = 0; i < 8 ; i++) {
		table[i] = calloc(8, sizeof(piece *));

		if (i == 0 || i == 1 || i == 6 || i == 7)
			for (int j = 0; j < 8; j++)
				table[i][j] = calloc(1 , sizeof(piece));
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