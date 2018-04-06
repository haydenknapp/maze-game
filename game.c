#include <stdlib.h>
#include <time.h>

#include "maze_game.h"

void game_init(Game *game, char *map_file_name) {
	game->board = malloc(sizeof(Board));
	board_init(game->board, map_file_name);
	game->gui = malloc(sizeof(Gui));
	gui_init(game->gui, game->board);
}

void game_destroy(Game *game) {
	gui_destroy(game->gui);
	free(game->gui);
	board_destroy(game->board);
	free(game->board);
}

void game_play(Game *game) {
	while (!board_player_win(game->board)) {

	}
}
