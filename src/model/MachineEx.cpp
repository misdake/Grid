#include "MachineEx.h"

#include "../program/ProgramEx.h"

#include "Grid.h"

MachineEx::MachineEx(const MachinePrototype& prototype)
        : Machine(prototype) {
}
void MachineEx::runEx(Grid& grid, Block& block, ProgramEx& program) {
    size_t min = 0, max = program.instructions.size() - 1;
    size_t pointer = 0;

//    params

    while (pointer <= max) {
        InstructionEx& instEx = program.instructionExList[pointer];
        int8_t cost = instEx.cost({grid, block, program, instEx});
        if (!block.tryCost(cost)) {
            printf("dead\n");
            break;
        } else {
            std::string s = grid.getPrinter().gen(program.instructions[pointer]);
            printf("(%d) %s\n", cost, s.c_str());
        }

        jumpdiff i = Machine::run(program.instructions[pointer]);
        pointer += i + 1;
        if (pointer < min) pointer = min;
    }
}

