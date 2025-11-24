#ifndef LOGICINFERENCEENGINE_H
#define LOGICINFERENCEENGINE_H

#include "Module.h"

class LogicInferenceEngine : public Module {
private:
    char premises[50][100];
    char conclusions[50][100];
    int ruleCount;

    int findFact(const char facts[][100], int factCount, const char* fact) const;

public:
    LogicInferenceEngine();

    void addRule();        
    void checkInference(); 
    void run() override;
};

#endif
