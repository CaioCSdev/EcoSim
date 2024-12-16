#ifndef STRUCTS_H
#define STRUCTS_H

#define RABBIT 'R'
#define FOX 'F'
#define ROCK '*'
#define EMPTY ' '

typedef struct {
  int age;
  short since_last_procreation;
  short since_last_meal;
  char species;
  int row;
  int col;
} Animal;

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
  int num_rabbits;
  int num_foxes;

  Animal **population;

  Animal **rabbits;
  Animal **foxes;
} World;

#endif // STRUCTS_H
