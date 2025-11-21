#define _CRT_SECURE_NO_WARNINGS

#include "CoursePrerequisiteManager.h"
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

CoursePrerequisiteManager::CoursePrerequisiteManager() : courseCount(0), prereqCount(0) {
    memset(courses, 0, sizeof(courses));
    memset(prereqCourse, 0, sizeof(prereqCourse));
    memset(prereqOf, 0, sizeof(prereqOf));
}

void CoursePrerequisiteManager::addCourse(const char* course) {
    if (courseCount < 50) {
        strcpy(courses[courseCount], course);
        courseCount++;
    }
}

void CoursePrerequisiteManager::addPrerequisite(const char* course, const char* prereq) {
    if (prereqCount < 100) {
        strcpy(prereqCourse[prereqCount], prereq);
        strcpy(prereqOf[prereqCount], course);
        prereqCount++;
    }
}

void CoursePrerequisiteManager::loadFASTCurriculum() {
    // SEMESTER 1
    addCourse("Programming Fundamentals");
    addCourse("Introduction to ICT");
    addCourse("Calculus and Analytical Geometry");
    addCourse("Applied Physics");
    addCourse("Islamic Studies");

    // SEMESTER 2
    addCourse("Object Oriented Programming");
    addCourse("Discrete Structures");
    addCourse("Digital Logic Design");
    addCourse("Communication Skills");
    addCourse("Pakistan Studies");

    addPrerequisite("Object Oriented Programming", "Programming Fundamentals");
    addPrerequisite("Digital Logic Design", "Applied Physics");

    // SEMESTER 3
    addCourse("Data Structures and Algorithms");
    addCourse("Database Systems");
    addCourse("Linear Algebra");
    addCourse("Differential Equations");
    addCourse("Technical and Business Writing");

    addPrerequisite("Data Structures and Algorithms", "Object Oriented Programming");
    addPrerequisite("Database Systems", "Programming Fundamentals");

    // SEMESTER 4
    addCourse("Operating Systems");
    addCourse("Computer Organization and Assembly");
    addCourse("Design and Analysis of Algorithms");
    addCourse("Theory of Automata");
    addCourse("Numerical Computing");

    addPrerequisite("Operating Systems", "Data Structures and Algorithms");
    addPrerequisite("Computer Organization and Assembly", "Digital Logic Design");
    addPrerequisite("Design and Analysis of Algorithms", "Data Structures and Algorithms");
    addPrerequisite("Theory of Automata", "Discrete Structures");

    // SEMESTER 5
    addCourse("Computer Networks");
    addCourse("Artificial Intelligence");
    addCourse("Software Engineering");
    addCourse("Parallel and Distributed Computing");
    addCourse("University Elective I");

    addPrerequisite("Computer Networks", "Operating Systems");
    addPrerequisite("Artificial Intelligence", "Data Structures and Algorithms");
    addPrerequisite("Software Engineering", "Object Oriented Programming");

    // SEMESTER 6
    addCourse("Information Security");
    addCourse("Human Computer Interaction");
    addCourse("Compiler Construction");
    addCourse("Advanced Database Systems");
    addCourse("University Elective II");

    addPrerequisite("Compiler Construction", "Theory of Automata");
    addPrerequisite("Compiler Construction", "Data Structures and Algorithms");
    addPrerequisite("Advanced Database Systems", "Database Systems");

    // SEMESTER 7
    addCourse("Final Year Project I");
    addCourse("Professional Practices");
    addCourse("Machine Learning");
    addCourse("Computer Graphics");
    addCourse("Department Elective I");

    addPrerequisite("Final Year Project I", "110 Credit Hours Completed");
    addPrerequisite("Machine Learning", "Artificial Intelligence");
    addPrerequisite("Machine Learning", "Linear Algebra");
    addPrerequisite("Machine Learning", "Calculus and Analytical Geometry");

    // SEMESTER 8
    addCourse("Final Year Project II");
    addCourse("Department Elective II");
    addCourse("Department Elective III");
    addCourse("Entrepreneurship");

    addPrerequisite("Final Year Project II", "Final Year Project I");
}

void CoursePrerequisiteManager::generateValidOrders() {
    cout << "\n=== Generating Valid Course Orders ===\n";

    cout << "\nRecommended Course Sequence:\n";
    cout << "Semester 1:\n";
    cout << "- Programming Fundamentals\n- Introduction to ICT\n- Calculus and Analytical Geometry\n- Applied Physics\n- Islamic Studies\n";

    cout << "\nSemester 2:\n";
    cout << "- Object Oriented Programming\n- Discrete Structures\n- Digital Logic Design\n- Communication Skills\n- Pakistan Studies\n";

    cout << "\nSemester 3:\n";
    cout << "- Data Structures and Algorithms\n- Database Systems\n- Linear Algebra\n- Differential Equations\n- Technical and Business Writing\n";

    cout << "\nSemester 4:\n";
    cout << "- Operating Systems\n- Computer Organization and Assembly\n- Design and Analysis of Algorithms\n- Theory of Automata\n- Numerical Computing\n";

    cout << "\nSemester 5:\n";
    cout << "- Computer Networks\n- Artificial Intelligence\n- Software Engineering\n- Parallel and Distributed Computing\n- University Elective I\n";

    cout << "\nSemester 6:\n";
    cout << "- Information Security\n- Human Computer Interaction\n- Compiler Construction\n- Advanced Database Systems\n- University Elective II\n";

    cout << "\nSemester 7:\n";
    cout << "- Final Year Project I\n- Professional Practices\n- Machine Learning\n- Computer Graphics\n- Department Elective I\n";

    cout << "\nSemester 8:\n";
    cout << "- Final Year Project II\n- Department Elective II\n- Department Elective III\n- Entrepreneurship\n";
}

void CoursePrerequisiteManager::run() {
    cout << "\n=== Course Prerequisite Manager ===\n";
    loadFASTCurriculum();

    int choice;
    do {
        cout << "\n1. Display All Courses\n";
        cout << "2. Display Prerequisites\n";
        cout << "3. Generate Valid Course Order\n";
        cout << "4. Check Course Prerequisites\n";
        cout << "5. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nAll Courses (" << courseCount << "):\n";
            for (int i = 0; i < courseCount; i++) {
                cout << i + 1 << ". " << courses[i] << endl;
            }
            break;

        case 2:
            cout << "\nAll Prerequisites:\n";
            for (int i = 0; i < prereqCount; i++) {
                cout << prereqCourse[i] << " -> " << prereqOf[i] << endl;
            }
            break;

        case 3:
            generateValidOrders();
            break;

        case 4: {
            char course[50];
            cout << "Enter course name: ";
            cin.ignore();
            cin.getline(course, 50);

            cout << "Prerequisites for " << course << ":\n";
            bool found = false;
            for (int i = 0; i < prereqCount; i++) {
                if (strcmp(prereqOf[i], course) == 0) {
                    cout << "- " << prereqCourse[i] << endl;
                    found = true;
                }
            }
            if (!found) cout << "No prerequisites found.\n";
            break;
        }
        }
    } while (choice != 5);
}