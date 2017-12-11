#include <iostream>
#include "Solver.h"

int main() {
    Solver solver;
    solver.loadPages();
    solver.solveConsole();
//    solver.outputDebug();
    return 0;
}