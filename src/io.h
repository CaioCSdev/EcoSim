#include "structs.h"
#include <stdio.h>

void show_map(int rows, int cols, char *map);
Ecosystem load_from_file(char *filename);
void show_ecosystem(Ecosystem ecosystem);
char *load_map(FILE *file, int rows, int cols);
