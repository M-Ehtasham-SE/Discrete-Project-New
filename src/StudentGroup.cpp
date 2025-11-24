#define _CRT_SECURE_NO_WARNINGS

#include "StudentGroup.h"
#include <iostream>
#include <cstring>
using namespace std;

class StudentGroupManager {
private:
    char students[100][50];
    char groups[100][50];
    char projects[50][50];
    int studentCount, groupCount, projectCount;

public:
    StudentGroupManager() : studentCount(0), groupCount(0), projectCount(0) {
        strcpy(groups[groupCount++], "CS-1A");
        strcpy(groups[groupCount++], "CS-1B");
        strcpy(groups[groupCount++], "CS-2A");

        strcpy(projects[projectCount++], "Database Project");
        strcpy(projects[projectCount++], "AI Research");
        strcpy(projects[projectCount++], "Web Application");
    }

    long long calculateCombinations(int n, int r) {
        if (r > n) return 0;
        if (r == 0 || r == n) return 1;

        long long result = 1;
        for (int i = 1; i <= r; i++) {
            result = result * (n - i + 1) / i;
        }
        return result;
    }

    void assignProjectGroups() {
        cout << "\n=== Project Group Assignment using Combinations ===\n";

        int totalStudents, groupSize;
        cout << "Enter total students: ";
        cin >> totalStudents;
        cout << "Enter students per group: ";
        cin >> groupSize;

        long long possibleGroups = calculateCombinations(totalStudents, groupSize);
        cout << "Possible group combinations: " << possibleGroups << endl;

        cout << "\nAssignment Principle:\n";
        cout << "- Each group has exactly " << groupSize << " students\n";
        cout << "- No student in multiple groups for same project\n";
        cout << "- Total groups formed: " << (totalStudents / groupSize) << endl;
    }

    void labSessionCombinations() {
        cout << "\n=== Lab Session Combinations ===\n";

        int labs = 3;
        int studentsPerLab = 4;

        cout << "Available Labs: Lab A, Lab B, Lab C\n";
        cout << "Students per lab: " << studentsPerLab << endl;

        long long assignments = 1;
        for (int i = 0; i < labs; i++) {
            assignments *= calculateCombinations(12 - i * 4, 4);
        }

        cout << "Possible lab assignment combinations: " << assignments << endl;
    }

    void electiveCombinations() {
        cout << "\n=== Elective Course Combinations ===\n";

        char electives[5][50] = {
            "Machine Learning", "Computer Vision",
            "Cyber Security", "Data Science", "Cloud Computing"
        };

        int choose = 2;
        long long combinations = calculateCombinations(5, choose);

        cout << "Available electives: 5\n";
        cout << "Electives to choose: " << choose << endl;
        cout << "Possible elective combinations: " << combinations << endl;

        cout << "\nCombinations:\n";
        int count = 1;
        for (int i = 0; i < 5; i++) {
            for (int j = i + 1; j < 5; j++) {
                cout << count++ << ". " << electives[i] << " + " << electives[j] << endl;
            }
        }
    }

    void run() {
        int choice;
        do {
            cout << "\n=== Student Group Combination Manager ===\n";
            cout << "1. Project Group Assignments\n";
            cout << "2. Lab Session Combinations\n";
            cout << "3. Elective Course Combinations\n";
            cout << "4. Combination Mathematics\n";
            cout << "5. Back to Main Menu\n";
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
            case 1: assignProjectGroups(); break;
            case 2: labSessionCombinations(); break;
            case 3: electiveCombinations(); break;
            case 4: {
                int n, r;
                cout << "Enter n and r for combination C(n,r): ";
                cin >> n >> r;
                cout << "C(" << n << "," << r << ") = " << calculateCombinations(n, r) << endl;
                break;
            }
            }
        } while (choice != 5);
    }
};

void StudentGroup::run() {
    StudentGroupManager manager;
    manager.run();
}