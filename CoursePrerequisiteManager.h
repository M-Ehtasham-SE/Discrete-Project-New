
#ifndef COURSEPREREQUISITEMANAGER_H
#define COURSEPREREQUISITEMANAGER_H

#include "Module.h"

class CoursePrerequisiteManager : public Module {
public:
    char courses[50][50];
    int courseCount;
    char prereqCourse[100][50];
    char prereqOf[100][50];
    int prereqCount;

    CoursePrerequisiteManager() : courseCount(0), prereqCount(0) {}

    void addCourse(const char* course);
    void addPrerequisite(const char* course, const char* prereq);
    void loadFASTCurriculum();
    void generateValidOrders();
    void run() override;
};

#endif