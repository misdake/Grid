#include "Generator.h"

#include <ctime>

std::uniform_int_distribution<> oprand_full_dist(-3, 3);
std::uniform_int_distribution<> oprand_reg_dist(0, 7);
std::uniform_int_distribution<> oprand_negative_dist(-3, -1);
std::uniform_int_distribution<> oprand_positive_dist(1, 3);
std::binomial_distribution<> oprand_binomial_dist(6, 0.5);

std::poisson_distribution<> program_length_binomial_dist(10);

uint8_t Generator::opIndex() {
    std::discrete_distribution<> opcode_dist(weights.begin(), weights.end());
    int r = opcode_dist(rng);
    return static_cast<uint8_t>(r);
}
int8_t Generator::oprand_full() {
    int r = oprand_full_dist(rng);
    return static_cast<int8_t>(r);
}
int8_t Generator::oprand_reg() {
    int r = oprand_reg_dist(rng);
    return static_cast<int8_t>(r);
}
int8_t Generator::oprand_positive() {
    int r = oprand_positive_dist(rng);
    return static_cast<int8_t>(r);
}
int8_t Generator::oprand_negative() {
    int r = oprand_negative_dist(rng);
    return static_cast<int8_t>(r);
}
int8_t Generator::oprand_binomial() {
    int r = oprand_binomial_dist(rng) - 3;
    return static_cast<int8_t>(r);
}

Generator::Generator() {
    rng.seed((unsigned int) std::time(nullptr));
}
Generator::Generator(uint32_t seed) {
    rng.seed(seed);
}

void Generator::registerInstruction(const InstGenEntry& entry) {
    weights.push_back(static_cast<int>(entry.weight));
    entries.push_back(entry);
}

InstructionEx Generator::generateInstruction() {
    InstructionEx r{};
    int index = opIndex();
    const InstGenEntry& entry = entries[index];
    r.opcode = entry.opcode;
    r.oprand0 = oprand(entry.oprand0rnd);
    r.oprand1 = oprand(entry.oprand1rnd);
    r.oprand2 = oprand(entry.oprand2rnd);
    r.cost = entry.costFunction(r.oprand0, r.oprand1, r.oprand2);
    return r;
}

int8_t Generator::oprand(OprandRnd rnd) {
    switch (rnd) {
        case OprandRnd::NONE: return 0;
        case OprandRnd::REG: return oprand_reg();
        case OprandRnd::FULL: return oprand_full();
        case OprandRnd::POSITIVE: return oprand_positive();
        case OprandRnd::NEGATIVE: return oprand_negative();
        case OprandRnd::BINOMIAL: return oprand_binomial();
    }
}

ProgramEx Generator::generateProgram() {
    int length = program_length_binomial_dist(rng);
    ProgramEx program{};
    for (int i = 0; i < length; i++) {
        InstructionEx instEx = generateInstruction();
        program.instructionExList.push_back(instEx);
        program.instructions.push_back(instEx.toInstruction());
    }
    return program;
}
