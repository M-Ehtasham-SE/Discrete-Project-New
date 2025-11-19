#include <iostream>
using namespace std;

#include "MainManager.h"

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
    cout << " 8. Functions Manager (Mappings)\n";
    cout << " 9. Logic & Inference Engine\n";
    cout << "10. Consistency Checker\n";
    cout << "11. Algorithmic Efficiency Benchmarks\n";
    cout << "12. Exit Program\n";
    cout << "==============================================\n";
    cout << "Enter your choice: ";
}

void MainManager::run()
{
    // static: state preserve between menu calls
    static CoursePrerequisiteManager courseManager;
    static StudentGroup           studentGroup;
    static SetOperationsManager   setManager;
    static RelationPropertiesChecker relationChecker;
    static ProofEngine            proofEngine;
    static InductionEngine        inductionEngine;
    static Tests                  testModule;

    static FunctionsManager       functionsManager;
    static LogicInferenceEngine   logicEngine;
    static ConsistencyChecker     consistencyChecker;
    static EfficiencyBenchmarks   efficiencyBenchmarks;

    choice = 0;

    while (choice != 12)
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
            functionsManager.run();
            break;
        case 9:
            logicEngine.run();
            break;
        case 10:
            consistencyChecker.run();
            break;
        case 11:
            efficiencyBenchmarks.run();
            break;
        case 12:
            cout << "\nExiting Program... Goodbye!\n";
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
            break;
        }
    }
}
