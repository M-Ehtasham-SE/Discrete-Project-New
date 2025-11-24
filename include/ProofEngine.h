#ifndef PROOFENGINE_H
#define PROOFENGINE_H

#include "Module.h"

class ProofEngine : public Module {
public:
    void provePrerequisiteChain();
    void proveLogicRule(const char* rule);
    void run() override;
};

#endif