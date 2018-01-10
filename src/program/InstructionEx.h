#pragma once

#include <cstdint>

#include <instruction/Instruction.h>

#include "../isa/isa.h"

struct InstructionEx {
    uint8_t opcode;
    int8_t oprand0;
    int8_t oprand1;
    int8_t oprand2;
    CostFunction cost;

    Instruction toInstruction() {
        auto code = static_cast<int16_t>(opcode);
        return {code, oprand0, oprand1, oprand2};
    }
};
