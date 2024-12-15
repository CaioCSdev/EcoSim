#include "io.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  Ecosystem state = load_from_file(argv[1]);
  // move through generations until state.N_GEN
  // move rabbits first
  show_ecosystem(state);
  output(state);
  return 0;
}
