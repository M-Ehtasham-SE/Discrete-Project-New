#include "FunctionsManager.h"
#include <iostream>
#include <cstring>
using namespace std;

FunctionsManager::FunctionsManager()
{
    mappingCount = 0;
    codomainCount = 0;
}

int FunctionsManager::findInCodomainSet(const char* value) const
{
    for (int i = 0; i < codomainCount; ++i) {
        if (strcmp(codomainSet[i], value) == 0)
            return i;
    }
    return -1;
}

int FunctionsManager::countCodomainOccurrences(const char* value) const
{
    int count = 0;
    for (int i = 0; i < mappingCount; ++i) {
        if (strcmp(course[i], value) == 0)
            ++count;
    }
    return count;
}

void FunctionsManager::addMapping()
{
    if (mappingCount >= 100) {
        cout << "Maximum number of mappings reached.\n";
        return;
    }

    char d[50], c[50];
    cin.ignore();
    cout << "Enter domain element (e.g. student name): ";
    cin.getline(d, 50);
    cout << "Enter codomain element (e.g. course name): ";
    cin.getline(c, 50);

    strcpy(domain[mappingCount], d);
    strcpy(codomain[mappingCount], c);
    mappingCount++;
    if (findInCodomainSet(c) == -1 && codomainCount < 100) {
        strcpy(codomainSet[codomainCount], c);
        codomainCount++;
    }

    cout << "Mapping added successfully: " << d << " -> " << c << "\n";
}

void FunctionsManager::checkInjective()
{
    if (mappingCount == 0) {
        cout << "No mappings available.\n";
        return;
    }

    bool injective = true;

    for (int i = 0; i < mappingCount; ++i) {
        for (int j = i + 1; j < mappingCount; ++j) {
           
            if (strcmp(student[i], course[j]) == 0 && strcmp(student[i], course[j]) != 0) {
                injective = false;
                cout << "Not injective because:\n";
                cout << "  " << student[i] << " -> " << course[i] << "\n";
                cout << "  " << student[j] << " -> " << course[j] << "\n";
            }
        }
    }

    if (injective)
        cout << "Function is injective (one-to-one).\n";
}

void FunctionsManager::checkSurjective()
{
    if (codomainCount == 0) {
        cout << "No codomain set defined yet.\n";
        return;
    }

    bool surjective = true;

    for (int i = 0; i < codomainCount; ++i) {
        int occ = countCodomainOccurrences(codomainSet[i]);
        if (occ == 0) {
            surjective = false;
            cout << "Not surjective because element '"
                << codomainSet[i] << "' in codomain is never mapped.\n";
        }
    }

    if (surjective)
        cout << "Function is surjective (onto).\n";
}

void FunctionsManager::checkBijective()
{
    if (mappingCount == 0 || codomainCount == 0) {
        cout << "Not enough data to check bijectivity.\n";
        return;
    }

    bool injective = true;
    for (int i = 0; i < mappingCount; ++i) {
        for (int j = i + 1; j < mappingCount; ++j) {
            if (strcmp(course[i], course[j]) == 0 &&
                strcmp(student[i], student[j]) != 0) {
                injective = false;
            }
        }
    }
    bool surjective = true;
    for (int i = 0; i < codomainCount; ++i) {
        int occ = countCodomainOccurrences(codomainSet[i]);
        if (occ == 0) {
            surjective = false;
        }
    }

    if (injective && surjective)
        cout << "Function is bijective.\n";
    else if (!injective && !surjective)
        cout << "Function is neither injective nor surjective.\n";
    else if (!injective)
        cout << "Function is surjective but not injective.\n";
    else
        cout << "Function is injective but not surjective.\n";
}

void FunctionsManager::run()
{
    int choice = 0;

    while (choice != 5) {
        cout << "\n=== Functions Manager ===\n";
        cout << "1. Add mapping (domain -> codomain)\n";
        cout << "2. Check Injective\n";
        cout << "3. Check Surjective\n";
        cout << "4. Check Bijective\n";
        cout << "5. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addMapping();
            break;
        case 2:
            checkInjective();
            break;
        case 3:
            checkSurjective();
            break;
        case 4:
            checkBijective();
            break;
        case 5:
            cout << "Returning to Main Menu...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }
}
