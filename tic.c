#include "tic.h"

#include <stdio.h>

int main() {
	printf("Starting tic-tac-toe...\n");

	play_game();

	printf("Thanks for playing!\n");
}

void clear_board(struct tile *tiles) {
	for (int i = 0; i < (COLUMNS * ROWS); i++) {
		tiles[i].value = ' ';
	}
}

void play_game() {
	struct tile tiles[9];
	for (int i = 0; i < (COLUMNS * ROWS); i++) {
		tiles[i].value = 'X';
	}

	clear_board(&tiles);

	print_board(tiles);
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
