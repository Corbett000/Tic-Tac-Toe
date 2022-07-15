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

void clear_board(struct tile*);
void play_game();
void print_board(struct tile*);

#define ROWS (3)
#define COLUMNS (3)