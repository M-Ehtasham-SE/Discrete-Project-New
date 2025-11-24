#define _CRT_SECURE_NO_WARNINGS
//Ehtasham Batalwi - 4
#include "MainManager.h"
#include <iostream>
using namespace std;

int main() {
    std::cout << "=== UNIDISC ENGINE - FAST University ===" << std::endl;
    std::cout << "Initializing System..." << std::endl;

    MainManager manager;
    manager.run();

    std::cout << "System Shutdown. Thank you!" << std::endl;
    return 0;
}