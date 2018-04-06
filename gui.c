#include <pthread.h>

#include <SDL2/SDL.h>

#include "maze_game.h"

typedef struct {
	int *flag;
	Board *board;
	int pixel_width;
	movements_t *movement;
	pthread_mutex_t *lock;
} gui_params;

static void gui_begin_render(void *params) {
	Board *board = ((gui_params *) params)->board;
	int *flag = ((gui_params *) params)->flag;
	int pixel_width = ((gui_params *) params)->pixel_width;
	int *movement = ((gui_params*) params)->movement;
	pthread_mutex_t *lock = ((gui_params*) params)->lock;

	int window_width = pixel_width * board->width,
	    window_height = pixel_width * board->height;

	SDL_Window *maze_window = SDL_CreateWindow("Maze Game", 100, 100, window_width, window_height, SDL_WINDOW_SHOWN);
	SDL_Renderer *maze_renderer = SDL_CreateRenderer(maze_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	while (*flag == rendering) {
		SDL_SetRenderDrawColor(maze_renderer, 255, 255, 255, 255 );
		SDL_RenderClear(maze_renderer);
		SDL_Event event;
		SDL_Rect r;
		for (int y = 0; y < board->height; ++y) {
			for (int x = 0; x < board->width; ++x) {
				r.x = x * pixel_width;
				r.y = y * pixel_width;
				r.w = pixel_width;
				r.h = pixel_width;

				tile_t tile_type = board_get_tile(board, x, y);

				if (tile_type == wall) {
					SDL_SetRenderDrawColor(maze_renderer, 0, 0, 0, 255);
					SDL_RenderFillRect(maze_renderer, &r);
				}
				else if (tile_type == start) {
					SDL_SetRenderDrawColor(maze_renderer, 255, 128, 128, 255);
					SDL_RenderFillRect(maze_renderer, &r);
				}
				else if (tile_type == path) {
					SDL_SetRenderDrawColor(maze_renderer, 128, 128, 255, 255);
					SDL_RenderFillRect(maze_renderer, &r);
				}
				else if (tile_type == end) {
					SDL_SetRenderDrawColor(maze_renderer, 128, 255, 128, 255);
					SDL_RenderFillRect(maze_renderer, &r);
				}
				while (SDL_PollEvent(&event)) {
					pthread_mutex_lock(lock);
					if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
								case SDLK_UP:
								*movement = up;
								break;
							case SDLK_DOWN:
								*movement = down;
								break;
							case SDLK_LEFT:
								*movement = left;
								break;
							case SDLK_RIGHT:
								*movement = right;
								break;
							default:
								break;
						}
					}
					pthread_mutex_unlock(lock);
				}

			}
		}
		r.x = player_x(board->player) * pixel_width;
		r.y = player_y(board->player) * pixel_width;
		SDL_SetRenderDrawColor(maze_renderer, 128, 128, 128, 255);
		SDL_RenderFillRect(maze_renderer, &r);
		SDL_RenderPresent(maze_renderer);
	}

	SDL_Delay(10);

	SDL_DestroyRenderer(maze_renderer);
	SDL_DestroyWindow(maze_window);
	SDL_Quit();
}

void gui_init(Gui *gui, Board *board) {
	gui->flag = rendering;
	gui_params params;
	params.board = board;
	params.flag = &gui->flag;
	params.pixel_width = 32;
	params.movement = &gui->movement;
	params.lock = &gui->lock;

	pthread_create(&gui->thread, NULL, (void *(*)(void *)) gui_begin_render, (void *) &params);
	SDL_Delay(10);
}

void gui_destroy(Gui *gui) {
	gui->flag = stop;
	pthread_join(gui->thread, NULL);
}

movements_t gui_movement(Gui *gui) {
	movements_t ret = gui->movement;
	pthread_mutex_lock(&gui->lock);
	gui->movement = -1;
	pthread_mutex_unlock(&gui->lock);
	return ret;
}
