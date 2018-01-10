#include "Block.h"

#include "Grid.h"

Block::Block(Grid& grid, uint16_t x, uint16_t y)
        : x(x),
          y(y),
          grid(grid),
          machine(new MachineEx(grid.getMachinePrototype())),
          program(nullptr) {
    energy = 0;
    defence = 0;
}

void Block::run() {
    if (program) {
        machine->runEx(grid, *this, *program);
    }
}