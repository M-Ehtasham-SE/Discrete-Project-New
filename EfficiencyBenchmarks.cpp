#include "EfficiencyBenchmarks.h"
#include <iostream>
using namespace std;

int EfficiencyBenchmarks::fibRecursive(int n)
{
    if (n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

int EfficiencyBenchmarks::fibMemoHelper(int n, int memo[])
{
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = fibMemoHelper(n - 1, memo) + fibMemoHelper(n - 2, memo);
    return memo[n];
}

void EfficiencyBenchmarks::showBits(unsigned int x)
{
    cout << "Bits: ";
    for (int i = 31; i >= 0; --i) {
        unsigned int mask = (1u << i);
        cout << ((x & mask) ? '1' : '0');
    }
    cout << "\n";
}

void EfficiencyBenchmarks::testRecursion()
{
    int n;
    cout << "Enter n for naive recursive Fibonacci: ";
    cin >> n;
    if (n < 0 || n > 40) {
        cout << "Choose n between 0 and 40 to avoid huge recursion.\n";
        return;
    }

    int result = fibRecursive(n);
    cout << "fibRecursive(" << n << ") = " << result << "\n";
    cout << "(Naive recursion grows exponentially.)\n";
}

void EfficiencyBenchmarks::testMemoization()
{
    int n;
    cout << "Enter n for memoized Fibonacci: ";
    cin >> n;
    if (n < 0 || n > 45) {
        cout << "Choose n between 0 and 45.\n";
        return;
    }

    int memo[50];
    for (int i = 0; i < 50; ++i) memo[i] = -1;

    int result = fibMemoHelper(n, memo);
    cout << "fibMemoized(" << n << ") = " << result << "\n";
    cout << "(Memoization reuses previous results, more efficient.)\n";
}

void EfficiencyBenchmarks::testBitsets()
{
    unsigned int x;
    cout << "Enter an integer (0 to 2^31-1) for bit operations: ";
    cin >> x;

    showBits(x);

    int bit;
    cout << "Enter bit position to set (0-31): ";
    cin >> bit;
    if (bit >= 0 && bit <= 31) {
        unsigned int y = x | (1u << bit);
        cout << "After setting bit " << bit << ":\n";
        showBits(y);
    }

    cout << "Enter bit position to clear (0-31): ";
    cin >> bit;
    if (bit >= 0 && bit <= 31) {
        unsigned int y = x & ~(1u << bit);
        cout << "After clearing bit " << bit << ":\n";
        showBits(y);
    }
}

void EfficiencyBenchmarks::run()
{
    int choice = 0;
    while (choice != 4) {
        cout << "\n=== Algorithmic Efficiency Benchmarks ===\n";
        cout << "1. Test Recursive Fibonacci\n";
        cout << "2. Test Memoized Fibonacci\n";
        cout << "3. Test Bit Manipulation (Bitset Style)\n";
        cout << "4. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            testRecursion();
            break;
        case 2:
            testMemoization();
            break;
        case 3:
            testBitsets();
            break;
        case 4:
            cout << "Returning to Main Menu...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }
}
