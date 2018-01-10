#pragma once

#include "InstructionEx.h"
#include "ProgramEx.h"
#include "../isa/isa.h"

//#include <random>
#include <vector>
#include <memory>

enum class OprandRnd {
    NONE, REG, FULL, POSITIVE, NEGATIVE, BINOMIAL
};
struct InstGenEntry {
    const char* opname;
    uint8_t opcode;
    uint8_t weight;
    OprandRnd oprand0rnd;
    OprandRnd oprand1rnd;
    OprandRnd oprand2rnd;
    CostFunction costFunction;
};

class Generator {
private:
//    std::mt19937 rng;

    std::vector<int> weights;
    std::vector<InstGenEntry> entries;

public:
    Generator();
//    explicit Generator(uint32_t seed);

    uint8_t opIndex() const;
    int8_t oprand(OprandRnd rnd) const;
    int8_t oprand_full() const;
    int8_t oprand_reg() const;
    int8_t oprand_positive() const;
    int8_t oprand_negative() const;
    int8_t oprand_binomial() const;

    void registerInstruction(const InstGenEntry& entry);
    InstructionEx generateInstruction() const;
    ProgramEx generateProgram() const;
};
