#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
  int GEN_PROC_RABBITS;
  int GEN_PROC_FOXES;
  int GEN_FOOD_FOXES;
  int N_GEN;
  int R;
  int C;
  int N;

  char *map;

  int GEN_COUNT;
} Ecosystem;

typedef struct {
  int age;
  int since_last_procreation;
  int x;
  int y;
} Rabbit;

typedef struct {
  int age;
  int x;
  int y;
} Fox;

#endif // STRUCTS_H
