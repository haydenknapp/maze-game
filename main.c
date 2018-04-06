#include "maze_game.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	Game game;
	game_init(&game, argv[1]);

	game_play(&game);

	game_destroy(&game);
}
