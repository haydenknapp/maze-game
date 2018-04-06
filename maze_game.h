#ifndef MAZE_GAME_
#define MAZE_GAME_

/////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {

} Gui;

/////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
	int x, y;
} Player;

#define player_x(W) (W->x)
#define player_y(W) (W->y)

/////////////////////////////////////////////////////////////////////////////////////////////////

enum TileTypes { player = 'a', path, wall, start, end };
typedef int tile_t;

// up means in the negative y direction
enum TileMovements { up, right, down, left };
typedef int movements_t;

typedef struct {
	int width, height;
	tile_t *tiles;
	Player *player;
} Board;

void board_init(Board *, char *);

void board_destroy(Board *);

void board_check_move_player(Board *, movements_t);

#define board_get_tile(W, X, Y) (W->tiles[Y * W->width + X])

#define board_player_win(W) (W->tiles[player_x(W->player) + player_y(W->player) * W->width] == end)

/////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
	Board *board;
} Game;

void game_init(Game *, char *);

void game_destroy(Game *);

void game_play(Game *);

#endif
