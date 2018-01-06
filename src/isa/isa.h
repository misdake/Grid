#pragma once

#include <cstdint>

class MachinePrototype;
class Generator;
class Instruction;

typedef int8_t(* CostFunction)(int8_t op1, int8_t op2, int8_t op3);

void defineISA(MachinePrototype& machine, Generator& generator);