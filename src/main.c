#include "io.h"

int main(int argc, char *argv[]) {
  Ecosystem state = load_from_file(argv[1]);
  show_ecosystem(state);
  return 0;
}
