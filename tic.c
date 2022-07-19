#include "tic.h"

#include <stdio.h>

int main() {
	printf("Starting tic-tac-toe...\n");

	char player_chars[] = "XO";
	int keep_playing = 1;
	while (keep_playing == 1) {
		printf("Please select an option:\n  1. Play Tic-Tac-Toe\n");
		printf("  2. Select Character\n  3. Select Board Size\n  4. Exit\n");
		int selection = 0;
		scanf_s("%d", &selection);
		switch (selection) {
		case 1:
			keep_playing = play_game(player_chars);
			break;
		case 2:
			select_character(player_chars);
			break;
		case 3:
			select_board();
			break;
		case 4:
			keep_playing = 0;
			break;
		default:
			printf("Invalid Selection!\n\n");
			break;
		}
		clear_buf();
	}

	printf("Thanks for playing!\n");
}

//Checks the board to determine if a player has won the game
int check_board(struct tile *tiles, char player_char) {
	//Check if a win occured on a row
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (tiles[(j * COLUMNS) + i].value != player_char) break;
			if (j == (ROWS - 1)) return 1;
		}
	}

	//Check if a win occured on a column
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (tiles[j + (i * COLUMNS)].value != player_char) break;
			if (j == (COLUMNS - 1)) return 1;
		}
	}

	//Ensure there won't be an out of bounds when checking the next win conditions
	if (COLUMNS != ROWS) return 0;

	//Check if a win occured on a diagonal
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

//Resets all of the board tiles to blank (' ')
void clear_board(struct tile *tiles) {
	for (int i = 0; i < (COLUMNS * ROWS); i++) {
		tiles[i].value = ' ';
	}
}

//Clears out the input buffer
void clear_buf() {
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

int play_game(char player_chars[]) {
	//Checks to make sure players are using different characters
	if (player_chars[0] == player_chars[1]) {
		printf("Error! Players must have different characters before playing.\n\n");
		select_character(player_chars);
		return 1;
	}

	struct tile tiles[9];
	clear_board(tiles);

	//The main game loop. Repeats until there is a draw or a winner
	for (int i = 1; i <= (ROWS * COLUMNS); i++) {
		int current_player = i % PLAYER_COUNT;
		if (current_player == 0) current_player = PLAYER_COUNT;

		print_board(tiles);
		printf("\nPlayer %d, Select a tile in format ROW-COLUMN.\n", current_player);
		
		int selected_row = 0;
		int selected_column = 0;
		int selected_tile = 0;

		//Takes input for where to place character and checks edge cases
		int repeat;
		do {
			repeat = 0;

			if (scanf_s("%d-%d", &selected_row, &selected_column) != 2) {
				clear_buf();
				printf("Incorrect format! 'ROW-COLUMN'\n");
				repeat = 1;
				continue;
			}

			selected_tile = (selected_row - 1) * COLUMNS + selected_column - 1;
			if ((selected_tile < 0) || (selected_tile >= (ROWS * COLUMNS))) {
				printf("Index selected is out of bounds! (%d-%d)\n", selected_row, selected_column);
				repeat = 1;
				continue;
			}

			if (tiles[selected_tile].value != ' ') {
				printf("Tile %d-%d has already been filled in! Select a different tile.\n", selected_row, selected_column);
				repeat = 1;
				continue;
			}
		} while (repeat == 1);

		//Update the chosen tile
		tiles[selected_tile].value = player_chars[current_player - 1];

		//Check if the current player won
		if (check_board(tiles, player_chars[current_player - 1]) == 1) {
			print_board(tiles);
			printf("\nCongrats Player %d! You Win!\n\n", current_player);
			printf("Would you like to: \n  1. Go to Main Menu\n  2. Exit\n");

			int selection = 1;
			clear_buf();
			scanf_s("%d", &selection);
			if (selection == 1) return 1;
			else return 2;
		}
	}

	//If the game is still running the result was a tie
	print_board(tiles);
	printf("\nThe game has ended in a draw!\n\n");
	printf("Would you like to: \n  1. Go to Main Menu\n  2. Exit\n");

	int selection = 1;
	clear_buf();
	scanf_s("%d", &selection);
	if (selection == 1) return 1;
	else return 2;
}

//Prints out the board into the terminal
void print_board(struct tile *tiles) {
	char row_s[] = " ROW  ";

	printf("\n       C O L\n     1   2   3\n");

	for (int i = 0; i < ROWS; i++) {
		printf(" %c %d", row_s[i * 2], (i + 1));
		for (int j = 0; j < COLUMNS; j++) {
			printf(" %c ", tiles[j + (COLUMNS * i)].value);
			if (j < 2) printf("|");
		}

		if (i < 2) printf("\n %c  ---+---+--- \n", row_s[i * 2 + 1]);
		else printf("\n\n");
	}
}

//TODO: ability to change the size of the board
void select_board() {
	return;
}

//Allows for the selection of any character. Defaults to 'X' and 'O'
void select_character(char *player_chars) {
	int ch = 0;
	printf("Player 1 is currently '%c',\nEnter a new character:\n", player_chars[0]);
	clear_buf();
	scanf_s("%c", &player_chars[0], 1);

	printf("Player 2 is currently '%c',\nEnter a new character:\n", player_chars[1]);
	clear_buf();
	scanf_s("%c", &player_chars[1], 1);
}