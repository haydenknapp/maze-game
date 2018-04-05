#include <stdlib.h>
#include <time.h>

#include "maze_game.h"

/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////

void board_init(Board *board, int width, int height) {
	board->width = width;
	board->height = height;

	board->tiles = malloc(width * height * sizeof(tile_t));
	for (int i = 0; i < width * height; ++i)
		board->tiles[i] = path;

	int start_x = 0;
	int start_y = 0;
	if (rand() % 2 == 0)
		start_x = rand() % board->width;
	else
		start_y = rand() % board->height;

	board_get_tile(board, start_x, start_y) = start;
}

void board_destroy(Board *board) {
	free(board->tiles);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void game_init(Game *game, int width, int height) {
	srand(time(NULL));
	game->board = malloc(sizeof(Board));
	board_init(game->board, width, height);
}

void game_destroy(Game *game) {
	board_destroy(game->board);
	free(game->board);
}
