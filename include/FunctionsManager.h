#ifndef FUNCTIONSMANAGER_H
#define FUNCTIONSMANAGER_H

#include "Module.h"

class FunctionsManager : public Module {
private:
    char students[100][50];      // Domain elements
    char courses[100][50];       // Codomain elements  
    int mappingCount;

    char codomainSet[100][50];
    int codomainCount;

    int findInCodomainSet(const char* value) const;
    int countCodomainOccurrences(const char* value) const;

public:
    FunctionsManager();

    void addMapping();
    void checkInjective();
    void checkSurjective();
    void checkBijective();

    void run() override;
};

#endif