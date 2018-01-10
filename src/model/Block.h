#pragma once

#include <cstdint>
#include <memory>

class Grid;

#include "MachineEx.h"
#include "../program/ProgramEx.h"

class Block {
private:
    Grid& grid;
    std::unique_ptr<MachineEx> machine;

    friend class Grid; //let grid access program, energy and defence
    std::unique_ptr<ProgramEx> program;
    uint16_t energy;
    uint16_t defence;

public:
    const uint16_t x;
    const uint16_t y;
    Block(Grid& grid, uint16_t x, uint16_t y);

    MachineEx* getMachine() { return machine.get(); }
    ProgramEx* getProgram() { return program.get(); }

    void run();

    bool tryCost(int8_t cost) {
        if(energy >= cost) {
            energy -= cost;
            return true;
        } else {
            return false;
        }
    }
};
