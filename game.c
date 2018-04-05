#include <stdlib.h>
#include <time.h>

#include "maze_game.h"

void game_init(Game *game, char *map_file_name) {
	srand(time(NULL));
	game->board = malloc(sizeof(Board));
	board_init(game->board, map_file_name);
}

void game_destroy(Game *game) {
	board_destroy(game->board);
	free(game->board);
}

void game_play(Game *game) {
	while (!board_player_win(game->board)) {

	}
}
