#pragma once

#include <program/Program.h>
#include "InstructionEx.h"

struct ProgramEx : public Program {
    std::vector<InstructionEx> instructionExList;
};
