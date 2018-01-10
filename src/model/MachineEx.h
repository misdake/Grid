#pragma once

#include <machine/Machine.h>

class Grid;
class Block;
class ProgramEx;

class MachineEx : public Machine {
public:
    explicit MachineEx(const MachinePrototype& prototype);

    void runEx(Grid& grid, Block& block, ProgramEx& program);
};