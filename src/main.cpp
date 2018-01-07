#include <iostream>

#include <isa/isa_all.h>
#include <instruction/Instruction.h>
#include <machine/Machine.h>
#include <instruction/Parser.h>
#include <instruction/Printer.h>

#include "program/Generator.h"

int main() {
    MachinePrototype prototype(16, 16);
    Generator generator;
    defineISA(prototype, generator);

    Printer printer(prototype);

    ProgramEx program = generator.generateProgram();
    printf("%s\n", printer.print(program).c_str());

    return 0;
}