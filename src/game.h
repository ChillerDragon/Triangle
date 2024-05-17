#ifndef SRC_GAME_H
#define SRC_GAME_H

#include <stdint.h>

struct World {
  int width;
  int height;
} typedef World;

struct GameState {
  long long game_start_time;
  long long current_tick;
  World world;
} typedef GameState;

extern GameState g;

#define SERVER_TICK_SPEED 50

long long tick_start_time(int tick);
void init_game();
float norm01(int value, int min, int max);
float world_coord_to_opengl_x(int x);
float world_coord_to_opengl_y(int y);

#endif
