#pragma once

#include <machine/Machine.h>

class MachineEx : public Machine {
public:
    MachineEx(const MachinePrototype& prototype);

    void run(const Program& program) override;
};