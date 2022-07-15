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

void clear_board(char* []);
void print_board(char* []);

#define ROWS (3)
#define COLUMNS (3)