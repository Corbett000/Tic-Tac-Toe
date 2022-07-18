struct tile
{
	char value;
};

struct row
{
	struct tile* tile_1;
	struct tile* tile_2;
	struct tile* tile_3;
};

int check_board(struct tile *, char);
void clear_board(struct tile *);
int play_game(char []);
void print_board(struct tile *);
void select_board();
void select_character(char *);

#define ROWS (3)
#define COLUMNS (3)
#define PLAYER_COUNT (2)