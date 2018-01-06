#include "MachineEx.h"

MachineEx::MachineEx(const MachinePrototype& prototype)
        : Machine(prototype) {
}

void MachineEx::run(const Program& program) {
    size_t min = 0, max = program.instructions.size() - 1;
    size_t pointer = 0;
    while (pointer <= max) {
        jumpdiff i = Machine::run(program.instructions[pointer]);
        pointer += i + 1;
        if (pointer < min) pointer = min;
    }
}
