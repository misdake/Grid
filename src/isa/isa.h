#pragma once

#include <cstdint>

class MachinePrototype;
class Generator;

class Grid;
class Block;
class ProgramEx;
class InstructionEx;
struct RunEnv {
    Grid& grid;
    Block& block;
    ProgramEx& prog;
    InstructionEx& inst;
};

typedef int8_t(* CostFunction)(const RunEnv& runEnv);

void defineISA(MachinePrototype& machine, Generator& generator);