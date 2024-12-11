#include "io.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

void show_map(int rows, int cols, char *map) {
  for (int i = 0; i < 1 + cols + 1; ++i)
    printf("-");
  printf("\n");

  for (int i = 0; i < rows; ++i) {
    printf("|");

    for (int j = 0; j < cols; ++j) {
      printf("%c", map[i * cols + j]);
    }

    printf("|\n");
  }
  for (int i = 0; i < 1 + cols + 1; ++i)
    printf("-");
  printf("\n");
}

void show_ecosystem(Ecosystem ecosystem) {
  printf("GEN_PROC_RABBITS: %d\n", ecosystem.GEN_PROC_RABBITS);
  printf("GEN_PROC_FOXES: %d\n", ecosystem.GEN_PROC_FOXES);
  printf("GEN_FOOD_FOXES: %d\n", ecosystem.GEN_FOOD_FOXES);
  printf("N_GEN: %d\n", ecosystem.N_GEN);
  printf("R: %d\n", ecosystem.R);
  printf("C: %d\n", ecosystem.C);
  printf("N: %d\n", ecosystem.N);
  show_map(ecosystem.R, ecosystem.C, ecosystem.map);
}

Ecosystem load_from_file(char *filename) {
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    printf("Error: Could not open file %s\n", filename);
    exit(1);
  }

  Ecosystem state;
  fscanf(file, "%d", &state.GEN_PROC_RABBITS);
  fscanf(file, "%d", &state.GEN_PROC_FOXES);
  fscanf(file, "%d", &state.GEN_FOOD_FOXES);
  fscanf(file, "%d", &state.N_GEN);
  fscanf(file, "%d", &state.R);
  fscanf(file, "%d", &state.C);
  fscanf(file, "%d", &state.N);

  // consume newline after last number
  char buffer[256];
  fgets(buffer, sizeof(buffer), file);

  state.map = load_map(file, state.R, state.C);

  fclose(file);

  return state;
}

char *load_map(FILE *file, int rows, int cols) {
  int i, row, col;
  char line[256];
  char sim[32];

  char *map = malloc(rows * cols * sizeof(char));
  for (i = 0; i < rows * cols; ++i)
    map[i] = ' ';

  while (fgets(line, sizeof(line), file)) {
    sscanf(line, "%s %d %d", sim, &row, &col);
    // the third character this different between a RABBIT, FOX and ROCK
    map[row * cols + col] = sim[2] == 'C' ? '*' : sim[0];
  }

  return map;
}
