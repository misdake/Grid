#include <iostream>

#include <isa/isa_all.h>
#include <instruction/Instruction.h>
#include <machine/Machine.h>
#include <instruction/Parser.h>
#include <instruction/Printer.h>

int main() {
    Machine machine(16);
    defineArithmetic(machine);
    defineJump(machine);
    defineMemory(machine);

    machine.defineN("hello_world", []() -> jumpdiff {
            std::cout << "Hello, World!" << std::endl;
            return 0;
        });
    machine.defineR("print_reg", [](Reg reg) -> jumpdiff {
        std::cout << reg.i << std::endl;
        return 0;
    });


    Parser parser(machine);
    Program program = parser.parseProgram(
            ""
                    "hello_world;"
                    "set r0, 0;"
                    "print_reg r0;"
                    "write_reg r0, r0;"
                    "add r0, 1;"
                    "jl r0, 10, -4;"
    );

    Printer printer(machine);
    std::string stringOutput = printer.print(program);
    std::cout << stringOutput << std::endl;

    machine.run(program);
    machine.printReg();

    return 0;
}