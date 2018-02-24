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

std::vector<InstRegEntry> isa = {
        //arithmetic
        {"abs_r",        1, OprandRnd::REG,      OprandRnd::NONE,     OprandRnd::NONE, [](const RunEnv& param) -> int8_t { return 1; }},
        {"set_ri",       1, OprandRnd::REG,      OprandRnd::BINOMIAL, OprandRnd::NONE, [](const RunEnv& param) -> int8_t { return 1; }},
        {"set_rr",       1, OprandRnd::REG,      OprandRnd::REG,      OprandRnd::NONE, [](const RunEnv& param) -> int8_t { return 1; }},
        {"add_ri",       1, OprandRnd::REG,      OprandRnd::BINOMIAL, OprandRnd::NONE, [](const RunEnv& param) -> int8_t { return 1; }},
        {"add_rr",       1, OprandRnd::REG,      OprandRnd::REG,      OprandRnd::NONE, [](const RunEnv& param) -> int8_t { return 1; }},
        {"mul_ri",       1, OprandRnd::REG,      OprandRnd::BINOMIAL, OprandRnd::NONE, [](const RunEnv& param) -> int8_t { return 2; }},
        {"mul_rr",       1, OprandRnd::REG,      OprandRnd::REG,      OprandRnd::NONE, [](const RunEnv& param) -> int8_t { return 2; }},
        //logic
        {"notl_r",       1, OprandRnd::REG,      OprandRnd::NONE,     OprandRnd::NONE, [](const RunEnv& param) -> int8_t { return 1; }},
        {"andl_rr",      1, OprandRnd::REG,      OprandRnd::REG,      OprandRnd::NONE, [](const RunEnv& param) -> int8_t { return 1; }},
        {"orl_rr",       1, OprandRnd::REG,      OprandRnd::REG,      OprandRnd::NONE, [](const RunEnv& param) -> int8_t { return 1; }},
        //jump
        {"skip_i",       1, OprandRnd::POSITIVE, OprandRnd::NONE,     OprandRnd::NONE, [](const RunEnv& param) -> int8_t { return 1; }},

        //get
        {"addDefense_i", 1, OprandRnd::POSITIVE, OprandRnd::NONE,     OprandRnd::NONE, [](const RunEnv& param) -> int8_t { return std::max((int8_t) 1, param.inst.oprand0); }},
};

void defineISA(MachinePrototype& machine, Generator& generator) {
    defineArithmetic(machine);
    defineJump(machine);
    defineLogic(machine);
    defineMemory(machine);

    machine.define("skip_i", "%s", OpType::I, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return instruction.oprand0.i;
    });

    machine.define("getX_r", "%s", OpType::R, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        machine.reg(instruction.oprand0.i) = machine.param(0);
        return 0;
    });
    machine.define("getY_r", "%s", OpType::R, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        machine.reg(instruction.oprand0.i) = machine.param(1);
        return 0;
    });
    machine.define("getEnergy_r", "%s", OpType::R, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        machine.reg(instruction.oprand0.i) = machine.param(2);
        return 0;
    });
    machine.define("getDefense_r", "%s", OpType::R, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        machine.reg(instruction.oprand0.i) = machine.param(3);
        return 0;
    });
    machine.define("isFamily_r", "%s", OpType::R, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        machine.reg(instruction.oprand0.i) = machine.param(3);
        return 0;
    });

    machine.define("addDefense_i", "%s", OpType::I, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        machine.param(3).i += std::max(1, instruction.oprand0.i);
        return 0;
    });

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
