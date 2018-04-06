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

	Player *player = game.board->player;

	// player movement tests
	player_x(game.board->player) = 1;
	player_y(game.board->player) = 0;

	board_check_move_player(game.board, up);
	assert(player_x(player) == 1);
	assert(player_y(player) == 0);

	board_check_move_player(game.board, down);
	assert(player_x(player) == 1);
	assert(player_y(player) == 1);

	board_check_move_player(game.board, down);
	assert(player_x(player) == 1);
	assert(player_y(player) == 1);

	board_check_move_player(game.board, right);
	assert(player_x(player) == 2);
	assert(player_y(player) == 1);

	board_check_move_player(game.board, left);
	assert(player_x(player) == 1);
	assert(player_y(player) == 1);

	board_check_move_player(game.board, left);
	assert(player_x(player) == 1);
	assert(player_y(player) == 1);

	for (int i = 0; i < 4; ++i)
		board_check_move_player(game.board, right);
	assert(player_x(player) == 5);
	assert(player_y(player) == 1);

	board_check_move_player(game.board, right);
	assert(player_x(player) == 5);
	assert(player_y(player) == 1);

	board_check_move_player(game.board, up);
	assert(player_x(player) == 5);
	assert(player_y(player) == 1);

	for (int i = 0; i < 5; ++i)
		board_check_move_player(game.board, down);
	assert(player_x(player) == 5);
	assert(player_y(player) == 6);

	for (int i = 0; i < 3; ++i)
		board_check_move_player(game.board, right);
	assert(player_x(player) == 8);
	assert(player_y(player) == 6);

	board_check_move_player(game.board, down);
	board_check_move_player(game.board, down);
	assert(player_x(player) == 8);
	assert(player_y(player) == 8);

	for (int i = 0; i < 4; ++i)
		board_check_move_player(game.board, left);
	assert(player_x(player) == 5);
	assert(player_y(player) == 8);

	game_destroy(&game);

#ifdef SECOND_TEST
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
#endif
}
