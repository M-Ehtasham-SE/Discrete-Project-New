#include "ConsistencyChecker.h"
#include <iostream>
#include <cstring>
using namespace std;

ConsistencyChecker::ConsistencyChecker()
{
    courseCount = 0;
    prereqCount = 0;
    facultyAssignCount = 0;
}

void ConsistencyChecker::checkCourseConflicts()
{
    cout << "\n=== Course Conflict Checker (time overlap) ===\n";
    cout << "How many course-time entries do you want to enter? ";
    cin >> courseCount;
    if (courseCount > 50) courseCount = 50;

    cin.ignore();
    for (int i = 0; i < courseCount; ++i) {
        cout << "Course " << (i + 1) << " name: ";
        cin.getline(courseNames[i], 50);
        cout << "Course " << (i + 1) << " time slot (e.g. Mon 9-11): ";
        cin.getline(courseTimes[i], 50);
    }

    bool conflictFound = false;
    for (int i = 0; i < courseCount; ++i) {
        for (int j = i + 1; j < courseCount; ++j) {
            if (strcmp(courseTimes[i], courseTimes[j]) == 0) {
                conflictFound = true;
                cout << "Conflict: '" << courseNames[i]
                    << "' and '" << courseNames[j]
                    << "' are both at " << courseTimes[i] << "\n";
            }
        }
    }

    if (!conflictFound) {
        cout << "No course time conflicts found.\n";
    }
}

void ConsistencyChecker::checkPrerequisiteViolations()
{
    cout << "\n=== Prerequisite Violation Checker ===\n";

    cout << "How many prerequisite rules (Course <- Prereq) do you want to enter? ";
    cin >> prereqCount;
    if (prereqCount > 50) prereqCount = 50;

    cin.ignore();
    for (int i = 0; i < prereqCount; ++i) {
        cout << "Rule " << (i + 1) << " - Enter course name: ";
        cin.getline(prereqOf[i], 50);
        cout << "Rule " << (i + 1) << " - Enter its prerequisite: ";
        cin.getline(prereqCourse[i], 50);
    }

    char targetCourse[50];
    cout << "\nEnter course student wants to take: ";
    cin.getline(targetCourse, 50);

    int completedCount;
    cout << "How many completed courses does the student have? ";
    cin >> completedCount;
    if (completedCount > 50) completedCount = 50;

    cin.ignore();
    char completed[50][50];
    for (int i = 0; i < completedCount; ++i) {
        cout << "Completed course " << (i + 1) << ": ";
        cin.getline(completed[i], 50);
    }

    bool violation = false;

    for (int i = 0; i < prereqCount; ++i) {
        if (strcmp(prereqOf[i], targetCourse) == 0) {
            bool found = false;
            for (int j = 0; j < completedCount; ++j) {
                if (strcmp(completed[j], prereqCourse[i]) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                violation = true;
                cout << "Violation: prerequisite '" << prereqCourse[i]
                    << "' for course '" << targetCourse
                    << "' is not completed.\n";
            }
        }
    }

    if (!violation) {
        cout << "No prerequisite violations for course '" << targetCourse << "'.\n";
    }
}

void ConsistencyChecker::checkFacultyRoomConflicts()
{
    cout << "\n=== Faculty-Room Conflict Checker ===\n";

    cout << "How many faculty-room-time assignments? ";
    cin >> facultyAssignCount;
    if (facultyAssignCount > 50) facultyAssignCount = 50;

    cin.ignore();
    for (int i = 0; i < facultyAssignCount; ++i) {
        cout << "Assignment " << (i + 1) << " - Faculty name: ";
        cin.getline(facultyNames[i], 50);
        cout << "Assignment " << (i + 1) << " - Room name: ";
        cin.getline(roomNames[i], 50);
        cout << "Assignment " << (i + 1) << " - Time slot: ";
        cin.getline(slotTimes[i], 50);
    }

    bool conflictFound = false;
    for (int i = 0; i < facultyAssignCount; ++i) {
        for (int j = i + 1; j < facultyAssignCount; ++j) {
            if (strcmp(roomNames[i], roomNames[j]) == 0 &&
                strcmp(slotTimes[i], slotTimes[j]) == 0) {
                conflictFound = true;
                cout << "Conflict: Room '" << roomNames[i]
                    << "' at time '" << slotTimes[i]
                    << "' assigned to both '" << facultyNames[i]
                    << "' and '" << facultyNames[j] << "'.\n";
            }
        }
    }

    if (!conflictFound) {
        cout << "No faculty-room-time conflicts found.\n";
    }
}

void ConsistencyChecker::run()
{
    int choice = 0;
    while (choice != 4) {
        cout << "\n=== Consistency Checker ===\n";
        cout << "1. Check Course Time Conflicts\n";
        cout << "2. Check Prerequisite Violations\n";
        cout << "3. Check Faculty-Room-Time Conflicts\n";
        cout << "4. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            checkCourseConflicts();
            break;
        case 2:
            checkPrerequisiteViolations();
            break;
        case 3:
            checkFacultyRoomConflicts();
            break;
        case 4:
            cout << "Returning to Main Menu...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }
}
