#ifndef CONSISTENCYCHECKER_H
#define CONSISTENCYCHECKER_H

#include "Module.h"

class ConsistencyChecker : public Module {
private:
    char courseNames[50][50];
    char courseTimes[50][50];
    int courseCount;

    char prereqCourse[50][50];
    char prereqOf[50][50];
    int prereqCount;

    char facultyNames[50][50];
    char roomNames[50][50];
    char slotTimes[50][50];
    int facultyAssignCount;

public:
    ConsistencyChecker();

    void checkCourseConflicts();
    void checkPrerequisiteViolations();
    void checkFacultyRoomConflicts();

    void run() override;
};

#endif
