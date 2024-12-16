#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

World populate_world(Ecosystem state) {
  Animal **population = (Animal **)malloc(state.R * state.C * sizeof(Animal *));
  int num_rabbits = 0;
  int num_foxes = 0;

  for (int i = 0; i < state.R * state.C; i++) {
    population[i] = malloc(sizeof(Animal));
    population[i]->age = 0;
    population[i]->since_last_procreation = 0;
    population[i]->since_last_meal = 0;
    population[i]->row = i / state.C;
    population[i]->col = i % state.C;

    if (state.map[i] == RABBIT) {
      population[i]->species = RABBIT;
      num_rabbits++;
    } else if (state.map[i] == FOX) {
      population[i]->species = FOX;
      num_foxes++;
    } else if (state.map[i] == '*') {
      population[i]->species = ROCK;
    } else {
      population[i]->species = EMPTY;
    }
  }

  Animal **rabbits = (Animal **)malloc(state.R * state.C * sizeof(Animal *));
  Animal **foxes = (Animal **)malloc(state.R * state.C * sizeof(Animal *));

  int rabbit_idx = 0;
  int fox_idx = 0;
  for (int i = 0; i < state.R * state.C; i++) {
    if (population[i]->species == RABBIT) {
      rabbits[rabbit_idx++] = population[i];
    } else if (population[i]->species == FOX) {
      foxes[fox_idx++] = population[i];
    }
  }
  rabbits[rabbit_idx] = NULL;
  foxes[fox_idx] = NULL;

  World world = {
      .num_rabbits = num_rabbits,
      .num_foxes = num_foxes,
      .population = population,
      .rabbits = rabbits,
      .foxes = foxes,
  };
  return world;
}

void update_animal(Animal *animal) {
  animal->since_last_meal += 1;
  animal->since_last_procreation += 1;
}

void kill(Animal *animal, Ecosystem *next_state, World *world) {
  int index = animal->row * next_state->C + animal->col;
  if (animal->species == RABBIT) {
#pragma omp atomic update
    world->num_rabbits--;
  } else {
#pragma omp atomic update
    world->num_foxes--;
  }
  animal->species = EMPTY;
  next_state->map[index] = ' ';
}

void swap_places(Animal *left, Animal *right, World *world,
                 Ecosystem *next_state) {
  int left_index = left->row * next_state->C + left->col;
  int right_index = right->row * next_state->C + right->col;

  world->population[left_index] = right;
  world->population[right_index] = left;
  next_state->map[left_index] = right->species;
  next_state->map[right_index] = left->species;

  int tmp_row = left->row;
  int tmp_col = left->col;
  left->row = right->row;
  left->col = right->col;
  right->row = tmp_row;
  right->col = tmp_col;
}

// must be called inside a critical section
void move_to(Animal *animal, int *position, Ecosystem *next_state,
             World *world) {
  printf("moving %c from (%d,%d) to (%d,%d)\n", animal->species, animal->row,
         animal->col, position[0], position[1]);
  int idx = position[0] * next_state->C + position[1];
  char at_position = next_state->map[idx];
  Animal *other = world->population[idx];

  if (animal->row == position[0] && animal->col == position[1]) {
    return;
  }

  if (animal->species == RABBIT) {
    if (at_position == RABBIT) {
      if (animal->since_last_procreation > other->since_last_procreation) {
        printf("animal %c at %d %d killed rabbit %c at %d %d\n", RABBIT,
               animal->row, animal->col, RABBIT, other->row, other->col);
        kill(other, next_state, world);
        swap_places(animal, other, world, next_state);
      } else {
        printf("animal R killed itself at %d %d\n", animal->row, animal->col);
        kill(animal, next_state, world);
      }
    } else {
      printf("animal %c at %d %d moved to empty space at %d %d\n", RABBIT,
             animal->row, animal->col, other->row, other->col);
      swap_places(animal, other, world, next_state);
    }
  } else {
    if (at_position == RABBIT) {
      kill(animal, next_state, world);
      animal->since_last_meal = -1;
      swap_places(animal, other, world, next_state);

    } else if (at_position == FOX) {
      if (animal->since_last_procreation > other->since_last_procreation) {
        kill(other, next_state, world);
        swap_places(animal, other, world, next_state);
      } else if (animal->since_last_procreation <
                 other->since_last_procreation) {
        kill(animal, next_state, world);
      } else if (animal->since_last_meal < other->since_last_meal) {
        kill(other, next_state, world);
        swap_places(animal, other, world, next_state);
      } else {
        kill(other, next_state, world);
      }
    } else {
      swap_places(animal, other, world, next_state);
    }
  }
}
