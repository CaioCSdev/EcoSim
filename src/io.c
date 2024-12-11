#include "io.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

void show_map() {
  printf("-------\n");
  printf("|* R F|\n");
  printf("|F   F|\n");
  printf("|    *|\n");
  printf("|R    |\n");
  printf("|R   F|\n");
  printf("-------\n");
}

void show_ecosystem(Ecosystem ecosystem) {
  printf("GEN_PROC_RABBITS: %d\n", ecosystem.GEN_PROC_RABBITS);
  printf("GEN_PROC_FOXES: %d\n", ecosystem.GEN_PROC_FOXES);
  printf("GEN_FOOD_FOXES: %d\n", ecosystem.GEN_FOOD_FOXES);
  printf("N_GEN: %d\n", ecosystem.N_GEN);
  printf("R: %d\n", ecosystem.R);
  printf("C: %d\n", ecosystem.C);
  printf("N: %d\n", ecosystem.N);
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

  fclose(file);

  return state;
}
