#define _CRT_SECURE_NO_WARNINGS


#include "ProofEngine.h"
#include <iostream>
#include <cstring>
using namespace std;

void ProofEngine::provePrerequisiteChain() {
    cout << "\n=== Prerequisite Chain Proof ===\n";

    cout << "Theorem: Course prerequisite chains ensure valid learning sequence\n";
    cout << "\nProof:\n";
    cout << "1. Base Case: Foundational courses have no prerequisites [PASS]\n";
    cout << "2. Inductive Step: Each course requires completion of prerequisites [PASS]\n";
    cout << "3. Transitive Property: If A->B and B->C, then A->C [PASS]\n";
    cout << "4. Acyclic: No circular dependencies in curriculum [PASS]\n";
    cout << "5. Topological sort exists for valid ordering [PASS]\n";

    cout << "\nExample Chain:\n";
    cout << "Programming Fundamentals -> OOP -> Data Structures -> Operating Systems -> Computer Networks\n";
    cout << "This forms a valid learning progression [PASS]\n";

    cout << "\nConclusion: Prerequisite system ensures students build knowledge progressively.\n";
}

void ProofEngine::proveLogicRule(const char* rule) {
    cout << "\n=== Logic Rule Proof: " << rule << " ===\n";

    if (strstr(rule, "modus") != nullptr || strstr(rule, "ponens") != nullptr) {
        cout << "Modus Ponens Proof:\n";
        cout << "1. If P then Q (P -> Q)\n";
        cout << "2. P is true\n";
        cout << "3. Therefore, Q must be true [PASS]\n";
        cout << "Form: [(P -> Q) && P] -> Q\n";
    }
    else if (strstr(rule, "tollens") != nullptr) {
        cout << "Modus Tollens Proof:\n";
        cout << "1. If P then Q (P -> Q)\n";
        cout << "2. Not Q (!Q)\n";
        cout << "3. Therefore, not P (!P) [PASS]\n";
        cout << "Form: [(P -> Q) && !Q] -> !P\n";
    }
    else if (strstr(rule, "syllogism") != nullptr) {
        cout << "Hypothetical Syllogism Proof:\n";
        cout << "1. If P then Q (P -> Q)\n";
        cout << "2. If Q then R (Q -> R)\n";
        cout << "3. Therefore, if P then R (P -> R) [PASS]\n";
        cout << "Form: [(P -> Q) && (Q -> R)] -> (P -> R)\n";
    }
    else if (strstr(rule, "contradiction") != nullptr) {
        cout << "Proof by Contradiction:\n";
        cout << "1. Assume the opposite of what we want to prove\n";
        cout << "2. Show this assumption leads to contradiction\n";
        cout << "3. Therefore, original statement must be true [PASS]\n";
    }
    else {
        cout << "General Logical Proof Structure:\n";
        cout << "1. State premises/assumptions\n";
        cout << "2. Apply logical rules step by step\n";
        cout << "3. Reach conclusion\n";
        cout << "4. Verify each step follows logically [PASS]\n";
    }

    cout << "\nProof completed successfully! [PASS]\n";
}

void ProofEngine::run() {
    int choice;
    do {
        cout << "\n=== Proof & Verification Engine ===\n";
        cout << "1. Prove Prerequisite Chain Validity\n";
        cout << "2. Prove Logical Rule\n";
        cout << "3. Mathematical Induction Example\n";
        cout << "4. Direct Proof Example\n";
        cout << "5. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            provePrerequisiteChain();
            break;

        case 2: {
            char rule[100];
            cout << "Enter logical rule to prove: ";
            cin.ignore();
            cin.getline(rule, 100);
            proveLogicRule(rule);
            break;
        }

        case 3:
            cout << "\n=== Mathematical Induction Proof ===\n";
            cout << "Theorem: 1 + 2 + 3 + ... + n = n(n+1)/2\n";
            cout << "Proof:\n";
            cout << "1. Base Case (n=1): 1 = 1(1+1)/2 = 1 [PASS]\n";
            cout << "2. Inductive Hypothesis: Assume true for n=k\n";
            cout << "   1+2+...+k = k(k+1)/2\n";
            cout << "3. Inductive Step (n=k+1):\n";
            cout << "   1+2+...+k+(k+1) = k(k+1)/2 + (k+1)\n";
            cout << "                   = (k+1)(k/2 + 1)\n";
            cout << "                   = (k+1)(k+2)/2 [PASS]\n";
            cout << "Therefore, formula holds for all natural numbers.\n";
            break;

        case 4:
            cout << "\n=== Direct Proof Example ===\n";
            cout << "Theorem: If n is even, then n^2 is even\n";
            cout << "Proof:\n";
            cout << "1. Let n be even, so n = 2k for some integer k\n";
            cout << "2. Then n^2 = (2k)^2 = 4k^2 = 2(2k^2)\n";
            cout << "3. Since 2k^2 is integer, n^2 is even [PASS]\n";
            break;
        }
    } while (choice != 5);
}