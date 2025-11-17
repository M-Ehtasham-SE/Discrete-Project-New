#include "RelationPropertiesChecker.h"
#include <iostream>
#include <cstring>
using namespace std;

class RelationChecker {
private:
    char set[10][50];
    int setSize;
    char relations[20][2][50];
    int relationCount;

public:
    RelationChecker() : setSize(0), relationCount(0) {}

    void inputSet() {
        cout << "Enter elements for the set (max 10, enter 'done' to finish):\n";
        setSize = 0;
        char element[50];

        while (setSize < 10) {
            cout << "Element " << setSize + 1 << ": ";
            cin.ignore();
            cin.getline(element, 50);

            if (strcmp(element, "done") == 0) break;

            strcpy(set[setSize], element);
            setSize++;
        }
    }

    void inputRelations() {
        if (setSize == 0) {
            cout << "Please input the set first!\n";
            return;
        }

        cout << "Enter relations (pairs a,b where aRb, enter 'done,done' to finish):\n";
        relationCount = 0;
        char a[50], b[50];

        while (relationCount < 20) {
            cout << "Relation " << relationCount + 1 << " (a,b): ";
            cin >> a;
            cin.ignore();
            cin.getline(b, 50);

            if (strcmp(a, "done") == 0 && strcmp(b, "done") == 0) break;

            strcpy(relations[relationCount][0], a);
            strcpy(relations[relationCount][1], b);
            relationCount++;
        }
    }

    void displayRelation() {
        cout << "Relation R = {";
        for (int i = 0; i < relationCount; i++) {
            cout << "(" << relations[i][0] << "," << relations[i][1] << ")";
            if (i < relationCount - 1) cout << ", ";
        }
        cout << "}\n";
    }

    bool isReflexive() {
        for (int i = 0; i < setSize; i++) {
            bool found = false;
            for (int j = 0; j < relationCount; j++) {
                if (strcmp(relations[j][0], set[i]) == 0 &&
                    strcmp(relations[j][1], set[i]) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
        return true;
    }

    bool isSymmetric() {
        for (int i = 0; i < relationCount; i++) {
            bool found = false;
            for (int j = 0; j < relationCount; j++) {
                if (strcmp(relations[i][0], relations[j][1]) == 0 &&
                    strcmp(relations[i][1], relations[j][0]) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
        return true;
    }

    bool isTransitive() {
        for (int i = 0; i < relationCount; i++) {
            for (int j = 0; j < relationCount; j++) {
                if (strcmp(relations[i][1], relations[j][0]) == 0) {
                    bool found = false;
                    for (int k = 0; k < relationCount; k++) {
                        if (strcmp(relations[k][0], relations[i][0]) == 0 &&
                            strcmp(relations[k][1], relations[j][1]) == 0) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) return false;
                }
            }
        }
        return true;
    }

    bool isAntiSymmetric() {
        for (int i = 0; i < relationCount; i++) {
            for (int j = 0; j < relationCount; j++) {
                if (strcmp(relations[i][0], relations[j][1]) == 0 &&
                    strcmp(relations[i][1], relations[j][0]) == 0) {
                    if (strcmp(relations[i][0], relations[i][1]) != 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void checkAllProperties() {
        cout << "\n=== Relation Properties Analysis ===\n";
        displayRelation();
        cout << "\nProperties:\n";

        bool reflexive = isReflexive();
        bool symmetric = isSymmetric();
        bool transitive = isTransitive();
        bool antisymmetric = isAntiSymmetric();

        cout << "- Reflexive: " << (reflexive ? "YES" : "NO") << endl;
        cout << "- Symmetric: " << (symmetric ? "YES" : "NO") << endl;
        cout << "- Transitive: " << (transitive ? "YES" : "NO") << endl;
        cout << "- Anti-symmetric: " << (antisymmetric ? "YES" : "NO") << endl;

        if (reflexive && symmetric && transitive) {
            cout << "\nThis is an EQUIVALENCE RELATION\n";
        }
        else if (reflexive && antisymmetric && transitive) {
            cout << "\nThis is a PARTIAL ORDER RELATION\n";
        }
        else {
            cout << "\nThis is a GENERAL RELATION\n";
        }
    }

    void run() {
        int choice;
        do {
            cout << "\n=== Relation Properties Checker ===\n";
            cout << "1. Input Set\n";
            cout << "2. Input Relations\n";
            cout << "3. Display Relation\n";
            cout << "4. Check All Properties\n";
            cout << "5. Check Individual Properties\n";
            cout << "6. Back to Main Menu\n";
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
            case 1: inputSet(); break;
            case 2: inputRelations(); break;
            case 3: displayRelation(); break;
            case 4: checkAllProperties(); break;
            case 5: {
                cout << "\nIndividual Properties:\n";
                cout << "Reflexive: " << (isReflexive() ? "YES" : "NO") << endl;
                cout << "Symmetric: " << (isSymmetric() ? "YES" : "NO") << endl;
                cout << "Transitive: " << (isTransitive() ? "YES" : "NO") << endl;
                cout << "Anti-symmetric: " << (isAntiSymmetric() ? "YES" : "NO") << endl;
                break;
            }
            }
        } while (choice != 6);
    }
};

void RelationPropertiesChecker::run() {
    RelationChecker checker;
    checker.run();
}