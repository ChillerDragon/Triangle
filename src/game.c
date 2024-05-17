#include "game.h"
#include "system.h"
#include <stdio.h>

long long tick_start_time(int tick) {
  return g.game_start_time + (time_freq() * tick) / SERVER_TICK_SPEED;
}

void init_game() {
  g.current_tick = 0;
  g.game_start_time = time_get();

  printf("%lld\n", g.game_start_time);
}
