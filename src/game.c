#include "game.h"
#include "system.h"
#include <stdio.h>

long long tick_start_time(int tick) {
  return g.game_start_time + (time_freq() * tick) / SERVER_TICK_SPEED;
}

void init_game() {
  g.current_tick = 0;
  g.game_start_time = time_get();
  g.world.width = 800;
  g.world.height = 600;

  printf("%lld\n", g.game_start_time);
}

float norm01(int value, int min, int max) {
  return (value - min) / (float)(max - min);
}

float world_coord_to_opengl_x(int x) {
  return norm01(x, 0, g.world.width) * 2 - 1;
}

float world_coord_to_opengl_y(int y) {
  return norm01(y, 0, g.world.height) * 2 - 1;
}
