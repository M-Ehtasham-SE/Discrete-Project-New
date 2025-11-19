#ifndef MAINMANAGER_H
#define MAINMANAGER_H

#include "Module.h"
#include "CoursePrerequisiteManager.h"
#include "StudentGroup.h"
#include "SetOperationsManager.h"
#include "RelationPropertiesChecker.h"
#include "ProofEngine.h"
#include "InductionEngine.h"
#include "Tests.h"

#include "FunctionsManager.h"
#include "LogicInferenceEngine.h"
#include "ConsistencyChecker.h"
#include "EfficiencyBenchmarks.h"

class MainManager {
public:
    int choice;
    void displayMenu();
    void run();
};

#endif
