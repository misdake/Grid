#pragma once

#include <cstdint>
#include <instruction/Instruction.h>

struct InstructionEx {
    uint8_t opcode;
    int8_t oprand0;
    int8_t oprand1;
    int8_t oprand2;
    int8_t cost;

    Instruction toInstruction() {
        int16_t code = (int16_t)opcode;
        return {code, oprand0, oprand1, oprand2};
    }
};
