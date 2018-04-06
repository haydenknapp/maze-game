#include "maze_game.h"

int main() {
	Game game;
	game_init(&game, "map1.txt");

	game_play(&game);

	game_destroy(&game);
}
