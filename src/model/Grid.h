#pragma once

#include <cstdint>
#include <vector>

#include <instruction/Printer.h>

#include "Block.h"
#include "../program/Generator.h"

class MachinePrototype;

class Grid {
private:
    const MachinePrototype& machinePrototype;
    const Printer& printer;
    const Generator& generator;

    std::vector<std::vector<Block>> blocks;

public:
    const uint16_t width;
    const uint16_t height;
    Grid(uint16_t width, uint16_t height, const MachinePrototype& machinePrototype, const Printer& printer, const Generator& generator);
    ~Grid() {};

    Block& getBlock(uint16_t x, uint16_t y) {
        return blocks[x][y];
    }

    const MachinePrototype& getMachinePrototype() const {
        return machinePrototype;
    }
    const Printer& getPrinter() const {
        return printer;
    }

    void initialize();

    void envRun();
    void blockRun();
};
