#include "../src/movement.h"
#include "../src/structs.h"
#include <assert.h>
#include <stdio.h>

Ecosystem state = {.R = 3, .C = 3, .GEN_COUNT = 0, .map = "aA0bB1cC2"};

// Test when the entity is surrounded by rocks and cannot move in any direction.
void test_surrounded_by_rocks() {
  Ecosystem state_now = state;
  state_now.map = "****.****";
  char result = move(1, 1, state_now);
  printf("%c\n", result);
  assert(result == 'X');
  printf("test_surrounded_by_rocks passed.\n");
}

// Test the move function with x, y at the grid boundaries.
void test_at_grid_lower_boundaries() {
  char result = move(0, 0, state);
  assert(result == 'E');
  printf("test_at_grid_boundaries passed.\n");
}

void test_at_grid_higher_boundaries() {
  char result = move(2, 2, state);
  assert(result == 'N');
  printf("test_at_grid_boundaries passed.\n");
}

// Test the move function when all possible directions are blocked.
void test_all_directions_outbounds() {
  Ecosystem state_now = state;
  state_now.C = 1;
  state_now.R = 1;
  char result = move(0, 0, state_now);
  assert(result == 'X');
  printf("test_all_directions_outbounds passed.\n");
}

// Test the move function when only one direction is possible.
void test_one_direction_possible_north() {
  Ecosystem state_now = state;
  state_now.map = "aA1*.*c*0";
  state_now.GEN_COUNT = 15;
  char result = move(1, 1, state_now);
  assert(result == 'N');
  printf("test_one_direction_possible_north passed.\n");
}

void test_one_direction_possible_east() {
  Ecosystem state_now = state;
  state_now.map = "a*1*.1c*2";
  state_now.GEN_COUNT = 15;
  char result = move(1, 1, state_now);
  assert(result == 'E');
  printf("test_one_direction_possible_east passed.\n");
}

void test_one_direction_possible_south() {
  Ecosystem state_now = state;
  state_now.map = "a*1*.*cC2";
  state_now.GEN_COUNT = 15;
  char result = move(1, 1, state_now);
  assert(result == 'S');
  printf("test_one_direction_possible_south passed.\n");
}

void test_one_direction_possible_west() {
  Ecosystem state_now = state;
  state_now.map = "a*0b.*c*2";
  state_now.GEN_COUNT = 15;
  char result = move(1, 1, state_now);
  assert(result == 'W');
  printf("test_one_direction_possible_west passed.\n");
}

// Test move function when multiple directions are possible, so gen count is
// used to determine the direction.
void test_multiple_directions_possible_south() {
  Ecosystem state_now = state;
  state_now.GEN_COUNT = 2 - 1 - 1; // x and y add 1 each
  // since all 4 are possible, 2 is South, so multiply by a multiple of 4 gets
  // always south.
  state_now.GEN_COUNT *= 16;
  char result = move(1, 1, state);
  assert(result == 'S');
  printf("test_multiple_directions_possible passed.\n");
}

int main() {
  test_surrounded_by_rocks();
  test_at_grid_lower_boundaries();
  test_at_grid_higher_boundaries();
  test_all_directions_outbounds();
  test_one_direction_possible_north();
  test_one_direction_possible_east();
  test_one_direction_possible_south();
  test_one_direction_possible_west();
  test_multiple_directions_possible_south();
  return 0;
}
