#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "maze_game.h"

static void print_maze(Board *board) {
	for (int y = 0; y < board->height; ++y) {
		for (int x = 0; x < board->width; ++x) {
			printf("%c ", board_get_tile(board, x, y));
		}
		printf("\n");
	}
}

int main() {
	// maze_game tests
	Game game;

	game_init(&game, "map1.txt");

	assert(game.board->width == 16);
	assert(game.board->height == 12);

	//print_maze(game.board);

	assert(player_x(game.board->player) == 1);
	assert(player_y(game.board->player) == 0);

	player_x(game.board->player) = 7;
	player_y(game.board->player) = 11;
	assert(board_player_win(game.board));

	game_destroy(&game);

	// second maze_game tests
	game_init(&game, "map2.txt");

	assert(game.board->width == 8);
	assert(game.board->height == 8);

	//print_maze(game.board);

	assert(player_x(game.board->player) == 7);
	assert(player_y(game.board->player) == 2);

	player_x(game.board->player) = 0;
	player_y(game.board->player) = 2;
	assert(board_player_win(game.board));

	game_destroy(&game);
}
