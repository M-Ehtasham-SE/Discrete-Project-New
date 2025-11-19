#include "LogicInferenceEngine.h"
#include <iostream>
#include <cstring>
using namespace std;

LogicInferenceEngine::LogicInferenceEngine()
{
    ruleCount = 0;
}
int LogicInferenceEngine::findFact(const char facts[][100],
    int factCount,
    const char* fact) const
{
    for (int i = 0; i < factCount; ++i) {
        if (strcmp(facts[i], fact) == 0)
            return i;
    }
    return -1;
}
void LogicInferenceEngine::addRule()
{
    if (ruleCount >= 50) {
        cout << "Maximum number of rules reached.\n";
        return;
    }

    char p[100], c[100];
    cin.ignore();
    cout << "Enter premise (IF part): ";
    cin.getline(p, 100);
    cout << "Enter conclusion (THEN part): ";
    cin.getline(c, 100);

    strcpy(premises[ruleCount], p);
    strcpy(conclusions[ruleCount], c);
    ruleCount++;

    cout << "Rule added: IF " << p << " THEN " << c << "\n";
}

void LogicInferenceEngine::checkInference()
{
    if (ruleCount == 0) {
        cout << "No rules defined.\n";
        return;
    }

    char knownFacts[100][100];
    int factCount = 0;

    int n;
    cout << "How many initial facts do you want to enter? ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n && i < 100; ++i) {
        cout << "Enter fact " << (i + 1) << ": ";
        cin.getline(knownFacts[factCount], 100);
        factCount++;
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < ruleCount; ++i) {
            if (findFact(knownFacts, factCount, premises[i]) != -1) {
                if (findFact(knownFacts, factCount, conclusions[i]) == -1) {
                    strcpy(knownFacts[factCount], conclusions[i]);
                    factCount++;
                    changed = true;
                    cout << "Inferred new fact: " << conclusions[i] << "\n";
                }
            }
        }
    }

    cout << "\nAll reachable facts using given rules:\n";
    for (int i = 0; i < factCount; ++i) {
        cout << "- " << knownFacts[i] << "\n";
    }
}

void LogicInferenceEngine::run()
{
    int choice = 0;
    while (choice != 3) {
        cout << "\n=== Logic & Inference Engine ===\n";
        cout << "1. Add Rule (IF P THEN Q)\n";
        cout << "2. Check Inference from Facts\n";
        cout << "3. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addRule();
            break;
        case 2:
            checkInference();
            break;
        case 3:
            cout << "Returning to Main Menu...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }
}
