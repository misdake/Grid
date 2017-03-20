#include <iostream>

#include <isa/isa_all.h>
#include <instruction/Instruction.h>
#include <machine/Machine.h>
#include <instruction/Parser.h>
#include <instruction/Printer.h>

class MachineEx : public Machine {
public:
    MachineEx(const MachinePrototype& prototype)
            : Machine(prototype) {
    }

    void run(const Program& program) override {
        size_t min = 0, max = program.instructions.size() - 1;
        size_t pointer = 0;
        while (pointer <= max) {
            jumpdiff i = Machine::run(program.instructions[pointer]);
            pointer += i + 1;
            if (pointer < min) pointer = min;
        }
    }
};

int main() {
    MachinePrototype prototype(16, 16);
    defineArithmetic(prototype);
    defineJump(prototype);
    defineMemory(prototype);

    prototype.defineN("hello_world", []() -> jumpdiff {
        std::cout << "Hello, World!" << std::endl;
        return 0;
    });
    prototype.defineR("print_reg", [](Reg reg) -> jumpdiff {
        std::cout << reg.i << std::endl;
        return 0;
    });

    Parser parser(prototype);
    Program program = parser.parseProgram(
            ""
                    "hello_world;"
                    "set r0, 0;"
                    "print_reg r0;"
                    "write_reg r0, r0;"
                    "add r0, 1;"
                    "jl r0, 10, -4;"
    );

    Printer printer(prototype);
    std::string stringOutput = printer.print(program);
    std::cout << stringOutput << std::endl;

    MachineEx machine(prototype);
    machine.run(program);

    return 0;
}