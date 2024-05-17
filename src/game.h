#ifndef SRC_GAME_H
#define SRC_GAME_H

#include <stdint.h>

struct GameState {
  long long game_start_time;
  long long current_tick;
} typedef GameState;

extern GameState g;

#define SERVER_TICK_SPEED 50

long long tick_start_time(int tick);
void init_game();

#endif
