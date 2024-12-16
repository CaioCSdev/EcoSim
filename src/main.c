#include "io.h"
#include "movement.h"
#include "simulation.h"
#include "structs.h"
#include <omp.h>
#include <stdlib.h>
#include <string.h>

omp_lock_t *create_locks(Ecosystem state) {
  omp_lock_t *locks = malloc(sizeof(omp_lock_t) * state.C * state.R);
  for (int i = 0; i < state.C * state.R; i++) {
    omp_init_lock(&locks[i]);
  }
  return locks;
}

#include <stdio.h> // Include for debug prints

void set_lock(omp_lock_t *locks, int *position, Ecosystem state) {
  int idx = position[0] * state.C + position[1];
  if (idx < 0 || idx >= state.C * state.R) {
    fprintf(stderr, "Error: Index out of bounds in set_lock: %d\n", idx);
    fprintf(stderr, "Position: (%d,%d)\n", position[0], position[1]);
    return;
  }
  omp_set_lock(&locks[idx]);
}

void unset_lock(omp_lock_t *locks, int *position, Ecosystem state) {
  int idx = position[0] * state.C + position[1];
  if (idx < 0 || idx >= state.C * state.R) {
    fprintf(stderr, "Error: Index out of bounds in unset_lock: %d\n", idx);
    return;
  }
  omp_unset_lock(&locks[idx]);
}

Ecosystem duplicate_state(Ecosystem state) {
  Ecosystem next_gen_state = state;
  next_gen_state.map = malloc(sizeof(char) * state.R * state.C);
  memcpy(next_gen_state.map, state.map, sizeof(char) * state.R * state.C);
  return next_gen_state;
}

int main(int argc, char *argv[]) {
  int i;
  int *position = malloc(sizeof(int) * 2);
  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  Ecosystem state = load_from_file(argv[1]);
  Ecosystem next_gen_state = duplicate_state(state);
  World world = populate_world(state);
  omp_lock_t *locks = create_locks(state);

  // #pragma omp parallel if (0) num_threads(1)
  {
    for (i = 0; i < world.num_rabbits; i++) {
      Animal *rabbit = world.rabbits[i];
      char direction = rabbit_move(rabbit->row, rabbit->col, state);
      new_position(rabbit->row, rabbit->col, direction, position);
      // set_lock(locks, position, state);
      // start critical section
      printf("moving %c from (%d,%d) to (%d,%d)\n", rabbit->species,
             rabbit->row, rabbit->col, position[0], position[1]);
      move_to(rabbit, position, &next_gen_state, &world);
      update_animal(rabbit);
      // end critical section
      // unset_lock(locks, position, state);
    }
    show_ecosystem(state);
    show_ecosystem(next_gen_state);
  }
  return 0;
}
