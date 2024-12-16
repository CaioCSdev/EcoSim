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
  int i, n, j;
  int *position;
  char direction;
  Animal *animal;
  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  Ecosystem state = load_from_file(argv[1]);
  Ecosystem next_gen_state = duplicate_state(state);
  World world = populate_world(state);
  omp_lock_t *locks = create_locks(state);
  for (j = 0; j < state.N_GEN; j++) {
    show_ecosystem(state);
    n = world.num_rabbits;
#pragma omp parallel for private(position, i, direction, animal)
    for (i = 0; i < n; i++) {
      position = malloc(sizeof(int) * 2);
      animal = world.rabbits[i];
#pragma omp critical
      direction = rabbit_move(animal->row, animal->col, state);
      new_position(animal->row, animal->col, direction, position);
      set_lock(locks, position, state);
      // start critical section
      move_to(animal, position, &next_gen_state, &world);
      update_animal(animal);
      // end critical section
      unset_lock(locks, position, state);
      free(position);
    }

    n = world.num_foxes;
#pragma omp parallel for private(position, i, direction, animal)
    for (i = 0; i < n; i++) {
      position = malloc(sizeof(int) * 2);
      animal = world.foxes[i];
      direction = fox_move(animal->row, animal->col, state);
#pragma omp critical
      new_position(animal->row, animal->col, direction, position);
      set_lock(locks, position, state);
      // start critical section
      move_to(animal, position, &next_gen_state, &world);
      update_animal(animal);
      // end critical section
      unset_lock(locks, position, state);
      free(position);
    }
    memcpy(state.map, next_gen_state.map, sizeof(char) * state.R * state.C);
    state.GEN_COUNT++;
    next_gen_state.GEN_COUNT++;
  }
  return 0;
}
