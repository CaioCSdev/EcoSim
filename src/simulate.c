void sim_move(int x, int y, char *map, int generation) {
  short idx = -1;
  char possible_moves[4] = {' '};
  if north (x, y, map)
    possible_moves[++idx] = 'N';
  if east (x, y, map)
    possible_moves[++idx] = 'E';
  if south (x, y, map)
    possible_moves[++idx] = 'S';
  if west (x, y, map)
    possible_moves[++idx] = 'W';

  char move = possible_moves[(generation + x + y) % idx];
}
