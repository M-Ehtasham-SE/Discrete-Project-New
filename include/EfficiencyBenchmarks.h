#ifndef EFFICIENCYBENCHMARKS_H
#define EFFICIENCYBENCHMARKS_H

#include "Module.h"

class EfficiencyBenchmarks : public Module {
private:
    int fibRecursive(int n);
    int fibMemoHelper(int n, int memo[]);
    void showBits(unsigned int x);

public:
    void testRecursion();
    void testMemoization();
    void testBitsets();

    void run() override;
};

#endif
