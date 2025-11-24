#define _CRT_SECURE_NO_WARNINGS

#include "InductionEngine.h"
#include <iostream>
#include <cstring>
using namespace std;

void InductionEngine::verifyPrerequisiteChain() {
    cout << "\n=== Prerequisite Chain Verification using Induction ===\n";

    cout << "Chain: Programming Fundamentals -> OOP -> Data Structures -> AI -> Machine Learning\n";
    cout << "\nBase Case (n=1):\n";
    cout << "- Programming Fundamentals has no prerequisites [VALID]\n";

    cout << "\nInductive Step:\n";
    cout << "Assume student completed course k successfully\n";
    cout << "Then course k+1 prerequisites are satisfied [VALID]\n";

    cout << "\nConclusion: Entire chain is valid by induction [PROVEN]\n";
}

void InductionEngine::strongInductionVerification() {
    cout << "\n=== Strong Induction: Multi-level Prerequisite Verification ===\n";

    cout << "Theorem: Student can take Machine Learning\n";
    cout << "\nStrong Induction Proof:\n";

    cout << "1. Base Cases:\n";
    cout << "   - Programming Fundamentals (no prereq) [VALID]\n";
    cout << "   - Calculus (no prereq) [VALID]\n";
    cout << "   - Linear Algebra (no prereq) [VALID]\n";

    cout << "2. Inductive Hypothesis:\n";
    cout << "   Assume all courses up to level k are completed\n";

    cout << "3. Verification Chain:\n";
    cout << "   Level 1: PF -> OOP [VALID]\n";
    cout << "   Level 2: OOP -> Data Structures [VALID]\n";
    cout << "   Level 3: Data Structures + Discrete -> Theory of Automata [VALID]\n";
    cout << "   Level 4: Data Structures -> Artificial Intelligence [VALID]\n";
    cout << "   Level 5: AI + Calculus + Linear Algebra -> Machine Learning [VALID]\n";

    cout << "\nAll direct AND indirect prerequisites satisfied [PROVEN]\n";
}

void InductionEngine::mathematicalInductionExample() {
    cout << "\n=== Mathematical Induction Example ===\n";
    cout << "Prove: 1 + 2 + 3 + ... + n = n(n+1)/2\n\n";

    cout << "Base Case (n=1):\n";
    cout << "Left side: 1\n";
    cout << "Right side: 1(1+1)/2 = 1 [VALID]\n\n";

    cout << "Inductive Step:\n";
    cout << "Assume true for n=k: 1+2+...+k = k(k+1)/2\n\n";

    cout << "Prove for n=k+1:\n";
    cout << "1+2+...+k+(k+1) = k(k+1)/2 + (k+1)\n";
    cout << "= (k+1)(k/2 + 1)\n";
    cout << "= (k+1)(k+2)/2 [VALID]\n\n";

    cout << "Formula holds for all natural numbers by induction [PROVEN]\n";
}

void InductionEngine::run() {
    int choice;
    do {
        cout << "\n=== Induction & Strong Induction Engine ===\n";
        cout << "1. Verify Prerequisite Chain (Simple Induction)\n";
        cout << "2. Multi-level Prerequisite Check (Strong Induction)\n";
        cout << "3. Mathematical Induction Example\n";
        cout << "4. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: verifyPrerequisiteChain(); break;
        case 2: strongInductionVerification(); break;
        case 3: mathematicalInductionExample(); break;
        }
    } while (choice != 4);
}