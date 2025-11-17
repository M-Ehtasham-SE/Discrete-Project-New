#ifndef INDUCTIONENGINE_H
#define INDUCTIONENGINE_H

#include "Module.h"

class InductionEngine : public Module {
public:
    void verifyPrerequisiteChain();
    void strongInductionVerification();
    void mathematicalInductionExample();
    void run() override;
};

#endif