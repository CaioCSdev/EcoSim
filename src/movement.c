#include "structs.h"

#define ROW 0
#define COL 1

int no_rock_at(int position[], Ecosystem state) {
  return (state.map[position[ROW] * state.C + position[COL]] != '*');
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
  short idx = -1;
  char possible_moves[4] = "XXXX";
  if (can_move_north(x, y, state))
    possible_moves[++idx] = 'N';
  if (can_move_east(x, y, state))
    possible_moves[++idx] = 'E';
  if (can_move_south(x, y, state))
    possible_moves[++idx] = 'S';
  if (can_move_west(x, y, state))
    possible_moves[++idx] = 'W';

  char move;
  if (idx == -1)
    move = 'X';
  else if (idx == 0)
    move = possible_moves[0];
  else
    move = possible_moves[(state.GEN_COUNT + x + y) % idx];

  return move;
}
