#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdio.h>

#include "maze_game.h"

#define MAX_MAP_BUFFER_SIZE 8

void board_init(Board *board, char *map_file_name) {
	FILE *map_file = fopen(map_file_name, "r");
	assert(map_file != NULL);

	char buffer[MAX_MAP_BUFFER_SIZE];

	fscanf(map_file, "%s", buffer);
	board->width = atoi(buffer);
	fscanf(map_file, "%s", buffer);
	board->height = atoi(buffer);

	int board_area = board->width * board->height;

	board->tiles = malloc(board_area * sizeof(tile_t));

	int i = 0;
	while (fscanf(map_file, "%s", buffer) != EOF)
		board->tiles[i++] = *buffer;

	fclose(map_file);

	board->player = malloc(sizeof(Player));

	int start_pos = -1;
	while (board->tiles[++start_pos] != start);
	player_y(board->player) = start_pos / board->width;
	player_x(board->player) = start_pos % board->width;
}

void board_destroy(Board *board) {
	free(board->player);
	free(board->tiles);
}

void board_check_move_player(Board *board, movements_t movement) {
	Player *player = board->player;

	int new_x = player_x(player), new_y = player_y(player);

	if (movement == up) {
		--new_y;
		tile_t tile_moved_to = board_get_tile(board, new_x, new_y);
		assert(new_y * board->width + new_x < board->height  * board->width);
		if ( new_y >= 0 && (tile_moved_to == path || tile_moved_to == end)) {
			player_y(player) = new_y;
		}
	}
	else if (movement == down) {
		++new_y;
		tile_t tile_moved_to = board_get_tile(board, new_x, new_y);
		assert(new_y * board->width + new_x < board->height  * board->width);
		if ( new_y < board->height && (tile_moved_to == path || tile_moved_to == end)) {
			player_y(player) = new_y;
		}
	}
	else if (movement == right) {
		++new_x;
		tile_t tile_moved_to = board_get_tile(board, new_x, new_y);
		assert(new_y * board->width + new_x < board->height  * board->width);
		if ( new_x >= 0 && (tile_moved_to == path || tile_moved_to == end)) {
			player_x(player) = new_x;
		}
	}
	else if (movement == left) {
		--new_x;
		tile_t tile_moved_to = board_get_tile(board, new_x, new_y);
		assert(new_y * board->width + new_x < board->height * board->width);
		if (new_x < board->height && (tile_moved_to == path || tile_moved_to == end)) {
			player_x(player) = new_x;
		}
	}
}
	


