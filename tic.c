#include "tic.h"

#include <stdio.h>

int main() {
	printf("Starting tic-tac-toe...\n");

	char player1_char = 'X';
	char player2_char = 'O';
	int keep_playing = 1;
	while (keep_playing == 1) {
		keep_playing = play_game(&player1_char, &player2_char);
	}

	printf("Thanks for playing!\n");
}

int check_board(struct tile* tiles, char player_char) {
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (tiles[j + (i * COLUMNS)].value != player_char) break;
			if (j == (ROWS - 1)) return 1;
		}
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (tiles[j + (i * ROWS)].value != player_char) break;
			if (j == (COLUMNS - 1)) return 1;
		}
	}

	//Ensure there won't be an out of bounds when checking the next win conditions
	if (COLUMNS != ROWS) return 0;

	for (int i = 0; i < ROWS; i++) {
		if (tiles[i + (i * COLUMNS)].value != player_char) break;
		if (i == (ROWS - 1)) return 1;
	}
	for (int i = 0; i < ROWS; i++) {
		if (tiles[i + (COLUMNS * (COLUMNS - i - 1))].value != player_char) break;
		if (i == (ROWS - 1)) return 1;
	}

	return 0;
}

void clear_board(struct tile *tiles) {
	for (int i = 0; i < (COLUMNS * ROWS); i++) {
		tiles[i].value = ' ';
	}
}

void clear_buf() {
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

int play_game(char* player1_char, char* player2_char) {
	printf("Please select an option:\n  1. Play Tic-Tac-Toe\n");
	printf("  2. Select Character\n  3. Select Board Size\n  4. Exit\n");
	int selection = 0;
	scanf_s("%d", &selection);
	switch (selection) {
		case 1:
			break;
		case 2:
			select_character(player1_char, player2_char);
			return 1;
		case 3:
			select_board();
			return 1;
		case 4:
			return 0;
		default:
			printf("Invalid Selection!\n\n");
			return 1;
	}

	while (*player1_char == *player2_char) {
		printf("Error! Players must have different characters before playing.\n\n");
		select_character(player1_char, player2_char);
		return 1;
	}

	struct tile tiles[9];
	for (int i = 0; i < (COLUMNS * ROWS); i++) {
		tiles[i].value = 'X';
	}
	clear_board(&tiles);

	print_board(tiles);

	return 1;
}

void print_board(struct tile *tiles) {
	printf("\n");

	for (int i = 0; i < ROWS; i++) {
		printf(" ");
		for (int j = 0; j < COLUMNS; j++) {
			printf(" %c ", tiles[j + (COLUMNS * i)].value);
			if (j < 2) printf("|");
		}

		if (i < 2) printf("\n ---+---+--- \n");
		else printf("\n\n");
	}
}

void select_board() {
	return;
}

void select_character(char* player1_char, char* player2_char) {
	int ch = 0;
	printf("Player 1 is currently '%c',\nEnter a new character:\n", *player1_char);
	clear_buf();
	scanf_s("%c", player1_char);

	printf("Player 2 is currently '%c',\nEnter a new character:\n", *player2_char);
	clear_buf();
	scanf_s("%c", player2_char);
}