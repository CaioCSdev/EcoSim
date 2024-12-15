#include "structs.h"

#define ROW 0
#define COL 1

int no_rock_at(int position[], Ecosystem state) {
  return (state.map[position[ROW] * state.C + position[COL]] != '*');
}

int no_rabbit_at(int position[], Ecosystem state) {
  return (state.map[position[ROW] * state.C + position[COL]] != 'R');
}

int in_bounds(int position[], Ecosystem state) {
  return ((position[ROW] >= 0) && (position[ROW] < state.R) &&
          (position[COL] >= 0) && (position[COL] < state.C));
}

int is_valid_move(int x, int y, Ecosystem state) {
  int position[] = {x, y};
  return (in_bounds(position, state) && no_rock_at(position, state));
}

int can_move_north(int x, int y, Ecosystem state) {
  return is_valid_move(x - 1, y, state);
}

int can_move_east(int x, int y, Ecosystem state) {
  return is_valid_move(x, y + 1, state);
}

int can_move_south(int x, int y, Ecosystem state) {
  return is_valid_move(x + 1, y, state);
}

int can_move_west(int x, int y, Ecosystem state) {
  return is_valid_move(x, y - 1, state);
}

char move(int x, int y, Ecosystem state) {
  short idx = 0;
  char possible_moves[4] = "XXXX";
  if (can_move_north(x, y, state))
    possible_moves[idx++] = 'N';
  if (can_move_east(x, y, state))
    possible_moves[idx++] = 'E';
  if (can_move_south(x, y, state))
    possible_moves[idx++] = 'S';
  if (can_move_west(x, y, state))
    possible_moves[idx++] = 'W';

  if (idx == 0)
    return 'X';
  else
    return possible_moves[(state.GEN_COUNT + x + y) % idx];
}

char rabbit_move(int x, int y, Ecosystem state) { return move(x, y, state); }

char fox_move(int x, int y, Ecosystem state) {
  /*
  Fox try to move to where are rabbits, if there are non then is just move.

  1. check rabbits
  2 if found:
      a. new tmp state.map with rocks where there is nothing
  else:
      a. new tmp state.map equal to the original
  3. run move with tmp state
  */
  char tmp_map[9] = {
      '*', '*', '*', // 012
      '*', ' ', '*', // 345
      '*', '*', '*'  // 678
  };

  Ecosystem tmp_micro_state = {
      .GEN_COUNT = state.GEN_COUNT + x + y - 2, // normalize gen count
      .N = 10, // n > c*r impossible flag state as fake
      .C = 3,
      .R = 3,
      .map = tmp_map,

  };
  int positions[4] = {1, 5, 7, 3}; // positions of the map

  int rabbit_possible_positions[4][2] = {
      {x - 1, y}, // north
      {x, y + 1}, // east
      {x + 1, y}, // south
      {x, y - 1}, // west
  };

  int rabbit_nearby = 0;
  for (int i = 0; i < 4; ++i) {
    if (in_bounds(rabbit_possible_positions[i], state) &&
        no_rabbit_at(rabbit_possible_positions[i], state)) {
      int debug_1 = positions[i];
      char debug_2 = tmp_micro_state.map[debug_1];
      tmp_micro_state.map[positions[i]] = '*';
    } else {
      tmp_micro_state.map[positions[i]] = 'R';
      rabbit_nearby = 1;
    }
  }

  if (rabbit_nearby)
    return move(1, 1, tmp_micro_state);
  else
    return move(x, y, state);
}
