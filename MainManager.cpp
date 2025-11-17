#include <iostream>
using namespace std;

#include "MainManager.h"
#include "CoursePrerequisiteManager.h"
#include "StudentGroup.h"
#include "SetOperationsManager.h"
#include "RelationPropertiesChecker.h"
#include "ProofEngine.h"
#include "InductionEngine.h"
#include "Tests.h"

void MainManager::displayMenu()
{
    cout << "\n";
    cout << "==============================================\n";
    cout << "        FAST University Discrete Project       \n";
    cout << "==============================================\n";
    cout << " 1. Course & Prerequisite Manager\n";
    cout << " 2. Student Group Combination Manager\n";
    cout << " 3. Set Operations Manager\n";
    cout << " 4. Relation Properties Checker\n";
    cout << " 5. Proof & Verification Engine\n";
    cout << " 6. Induction & Strong Induction Engine\n";
    cout << " 7. Run Unit Tests\n";
    cout << " 8. Exit Program\n";
    cout << "==============================================\n";
    cout << "Enter your choice: ";
}

void MainManager::run()
{
    CoursePrerequisiteManager courseManager;
    StudentGroup studentGroup;
    SetOperationsManager setManager;
    RelationPropertiesChecker relationChecker;
    ProofEngine proofEngine;
    InductionEngine inductionEngine;
    Tests testModule;

    choice = 0;

    while (choice != 8)
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            courseManager.run();
            break;

        case 2:
            studentGroup.run();
            break;

        case 3:
            setManager.run();
            break;

        case 4:
            relationChecker.run();
            break;

        case 5:
            proofEngine.run();
            break;

        case 6:
            inductionEngine.run();
            break;

        case 7:
            testModule.run();
            break;

        case 8:
            cout << "\nExiting Program... Goodbye!\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
            break;
        }
    }
}