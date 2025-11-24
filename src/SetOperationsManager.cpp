#define _CRT_SECURE_NO_WARNINGS

#include "SetOperationsManager.h"
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class SetManager {
private:
    char setA[10][50], setB[10][50];
    int countA, countB;

public:
    SetManager() : countA(0), countB(0) {}

    void inputSet(char set[10][50], int& count, const char* setName) {
        cout << "Enter elements for Set " << setName << " (max 10, enter 'done' to finish):\n";
        count = 0;
        char element[50];

        while (count < 10) {
            cout << "Element " << count + 1 << ": ";
            cin.ignore();
            cin.getline(element, 50);

            if (strcmp(element, "done") == 0) break;

            bool duplicate = false;
            for (int i = 0; i < count; i++) {
                if (strcmp(set[i], element) == 0) {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) {
                strcpy(set[count], element);
                count++;
            }
            else {
                cout << "Duplicate element! Skipping...\n";
            }
        }
    }

    void displaySet(char set[10][50], int count, const char* setName) {
        cout << setName << " = {";
        for (int i = 0; i < count; i++) {
            cout << set[i];
            if (i < count - 1) cout << ", ";
        }
        cout << "}\n";
    }

    void unionSets() {
        cout << "\nUnion of A and B: {";
        bool first = true;

        for (int i = 0; i < countA; i++) {
            if (!first) cout << ", ";
            cout << setA[i];
            first = false;
        }

        for (int i = 0; i < countB; i++) {
            bool found = false;
            for (int j = 0; j < countA; j++) {
                if (strcmp(setB[i], setA[j]) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                if (!first) cout << ", ";
                cout << setB[i];
                first = false;
            }
        }
        cout << "}\n";
    }

    void intersectionSets() {
        cout << "\nIntersection of A and B: {";
        bool first = true;

        for (int i = 0; i < countA; i++) {
            for (int j = 0; j < countB; j++) {
                if (strcmp(setA[i], setB[j]) == 0) {
                    if (!first) cout << ", ";
                    cout << setA[i];
                    first = false;
                    break;
                }
            }
        }
        cout << "}\n";
    }

    void differenceSets() {
        cout << "\nA - B: {";
        bool first = true;

        for (int i = 0; i < countA; i++) {
            bool found = false;
            for (int j = 0; j < countB; j++) {
                if (strcmp(setA[i], setB[j]) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                if (!first) cout << ", ";
                cout << setA[i];
                first = false;
            }
        }
        cout << "}\n";
    }

    void run() {
        int choice;
        do {
            cout << "\n=== Set Operations Manager ===\n";
            cout << "1. Input Set A\n";
            cout << "2. Input Set B\n";
            cout << "3. Display Sets\n";
            cout << "4. Union (A B)\n";
            cout << "5. Intersection (A B)\n";
            cout << "6. Difference (A - B)\n";
            cout << "7. Back to Main Menu\n";
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
            case 1: inputSet(setA, countA, "A"); break;
            case 2: inputSet(setB, countB, "B"); break;
            case 3:
                displaySet(setA, countA, "Set A");
                displaySet(setB, countB, "Set B");
                break;
            case 4: unionSets(); break;
            case 5: intersectionSets(); break;
            case 6: differenceSets(); break;
            }
        } while (choice != 7);
    }
};

void SetOperationsManager::run() {
    SetManager manager;
    manager.run();
}