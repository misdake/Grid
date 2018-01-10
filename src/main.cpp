#include <iostream>

#include <isa/isa_all.h>
#include <instruction/Instruction.h>
#include <machine/Machine.h>
#include <instruction/Parser.h>
#include <instruction/Printer.h>

#include "program/Generator.h"
#include "model/Grid.h"

int main() {
    MachinePrototype prototype(8, 16);
    Generator generator;
    defineISA(prototype, generator);

    Printer printer(prototype);

    Grid grid(1, 1, prototype, printer, generator);
    grid.initialize();

    Block& block = grid.getBlock(0, 0);
    printer.print(*block.getProgram());

    for(int i = 0; i < 5; i++) {
        grid.envRun();
        grid.blockRun();
        block.getMachine()->printReg();
        printf("--------------\n");
    }

    return 0;
}