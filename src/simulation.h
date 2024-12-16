#ifndef SIMULATION_H
#define SIMULATION_H

#include "structs.h"

World populate_world(Ecosystem state);
void update_animal(Animal *animal);
void move_to(Animal *animal, int *position, Ecosystem *state, World *world);

#endif /* SIMULATION_H */
