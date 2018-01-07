#include "isa.h"

#include <isa/isa_all.h>
#include <machine/Machine.h>

#include "../program/Generator.h"

struct InstRegEntry {
    const char* opname;
    const uint8_t weight;
    const OprandRnd oprand0rnd;
    const OprandRnd oprand1rnd;
    const OprandRnd oprand2rnd;
    const CostFunction costFunction;
};

const InstRegEntry isa[] = {
        //arithmetic
        {"abs_r", 1, OprandRnd::REG, OprandRnd::NONE, OprandRnd::NONE, [](int8_t op1, int8_t op2, int8_t op3) -> int8_t { return 1; }},
        {"set_ri", 1, OprandRnd::REG, OprandRnd::BINOMIAL, OprandRnd::NONE, [](int8_t op1, int8_t op2, int8_t op3) -> int8_t { return 1; }},
        {"set_rr", 1, OprandRnd::REG, OprandRnd::REG, OprandRnd::NONE, [](int8_t op1, int8_t op2, int8_t op3) -> int8_t { return 1; }},
        {"add_ri", 1, OprandRnd::REG, OprandRnd::BINOMIAL, OprandRnd::NONE, [](int8_t op1, int8_t op2, int8_t op3) -> int8_t { return 1; }},
        {"add_rr", 1, OprandRnd::REG, OprandRnd::REG, OprandRnd::NONE, [](int8_t op1, int8_t op2, int8_t op3) -> int8_t { return 1; }},
        {"mul_ri", 1, OprandRnd::REG, OprandRnd::BINOMIAL, OprandRnd::NONE, [](int8_t op1, int8_t op2, int8_t op3) -> int8_t { return 2; }},
        {"mul_rr", 1, OprandRnd::REG, OprandRnd::REG, OprandRnd::NONE, [](int8_t op1, int8_t op2, int8_t op3) -> int8_t { return 2; }},
        //logic
        {"notl_r", 1, OprandRnd::REG, OprandRnd::NONE, OprandRnd::NONE, [](int8_t op1, int8_t op2, int8_t op3) -> int8_t { return 1; }},
        {"andl_rr", 1, OprandRnd::REG, OprandRnd::REG, OprandRnd::NONE, [](int8_t op1, int8_t op2, int8_t op3) -> int8_t { return 1; }},
        {"orl_rr", 1, OprandRnd::REG, OprandRnd::REG, OprandRnd::NONE, [](int8_t op1, int8_t op2, int8_t op3) -> int8_t { return 1; }},
};

void defineISA(MachinePrototype& machine, Generator& generator) {
    defineArithmetic(machine);
    defineJump(machine);
    defineLogic(machine);
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
