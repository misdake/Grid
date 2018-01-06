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

    for (int i = 0; i != 5; i++) {
        InstructionEx c = generator.generateInstruction();
        Instruction instruction = c.toInstruction();
        printf("(%d) %s\n", c.cost, printer.print(instruction).c_str());
    }


    return 0;
}