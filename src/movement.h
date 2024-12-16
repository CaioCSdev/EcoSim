#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "structs.h"

char move(int x, int y, Ecosystem state);
char fox_move(int x, int y, Ecosystem state);
char rabbit_move(int x, int y, Ecosystem state);
int no_rabbit_at(int position[], Ecosystem state);
int *new_position(int x, int y, char direction, int *position);

#endif // MOVEMENT_H
