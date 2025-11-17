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

class MainManager {
public:
    int choice;
    void displayMenu();
    void run();
};

#endif