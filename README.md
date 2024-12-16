# EcoSim
Parallel Computing project for simulating an ecosystem


Hard to debug errors:
- Segmentation fault
  The issue with the position array having incorrect values likely stems from the way new_position is implemented. The function new_position returns a pointer to a temporary array created within the function. This array is allocated on the stack and becomes invalid once the function returns, leading to undefined behavior when accessed later.

  Accessing tmp_micro_state.map: The tmp_micro_state.map is initialized with a string literal "***" "* *" "***", which is a read-only memory region. Attempting to modify it will cause a segmentation fault.
