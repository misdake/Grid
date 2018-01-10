#include "Grid.h"

typedef std::function<void(Block&)> BlockFunction;

void foreach(Grid& grid, const BlockFunction& function) {
    for (uint16_t i = 0; i < grid.width; i++) {
        for (uint16_t j = 0; j < grid.height; j++) {
            function(grid.getBlock(i, j));
        }
    }
}

Grid::Grid(uint16_t width, uint16_t height,
           const MachinePrototype& machinePrototype,
           const Printer& printer,
           const Generator& generator)
        : width(width), height(height),
          machinePrototype(machinePrototype),
          printer(printer),
          generator(generator) {
    for (int i = 0; i < width; i++) {
        blocks.emplace_back();
        std::vector<Block>& vector = blocks[i];
        for (int j = 0; j < height; j++) {
            vector.emplace_back(*this, i, j);
        }
    }
}

void Grid::initialize() {
    foreach(*this, [this](Block& block) {
        block.program = std::unique_ptr<ProgramEx>(new ProgramEx(generator.generateProgram()));
        for (int i = 0; i < block.machine->registerCount; i++) {
            block.machine->reg(i).i = generator.oprand_full();
        }
    });
}

void Grid::envRun() {
    foreach(*this, [this](Block& block) {
        block.energy += 8;
    });
}
void Grid::blockRun() {
    foreach(*this, [this](Block& block) {
        block.run();
    });
}
