#include "isa.h"

#include <isa/isa_all.h>
#include <machine/Machine.h>

#include "../program/Generator.h"

struct InstRegEntry {
    const char* opname;
    uint8_t weight;
    OprandRnd oprand0rnd;
    OprandRnd oprand1rnd;
    OprandRnd oprand2rnd;
    CostFunction costFunction;
};

const InstRegEntry isa[] = {
        {"add_ri", 1, OprandRnd::REG, OprandRnd::BINOMIAL, OprandRnd::NONE, [](int8_t op1, int8_t op2, int8_t op3) -> int8_t { return 1; }},
};

void defineISA(MachinePrototype& machine, Generator& generator) {
    defineArithmetic(machine);
    defineJump(machine);
    defineMemory(machine);

    for (const InstRegEntry& e : isa) {
        InstGenEntry entry{
                e.opname,
                (uint8_t) machine.getOpCode(e.opname),
                e.weight,
                e.oprand0rnd,
                e.oprand1rnd,
                e.oprand2rnd,
                e.costFunction
        };
        generator.registerInstruction(entry);
    }
}
