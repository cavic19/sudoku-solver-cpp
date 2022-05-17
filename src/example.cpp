#include <iostream>
#include "Parser.h"
#include <string>
#include "CPSolver.h"
#include "Logging.h"
#include <chrono>
#include "BacktrackingSolver.h"

using namespace Sudoku;
using namespace std;
int main()
{


    string easyPuzzle = "..3.2.6..9..3.5..1..18.64....81.29..7.......8..67.82....26.95..8..2.3..9..5.1.3..;483921657967345821251876493548132976729564138136798245372689514814253769695417382";
    Parser parser(9, ';','.', -1);
    int puzzle[81];
    int expectedSollution[81];
    int actualSollution[81];
    parser.Parse(easyPuzzle, puzzle, expectedSollution);   
    CPSolver<3> solver;
    chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    solver.Solve(puzzle, actualSollution);
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Time CP: " << chrono::duration_cast<chrono::nanoseconds> (end - start).count() << "[ns]" << endl;

    int actualSollutionBc[81];
    BacktrackingSolver<3> bcSolver;
    start = std::chrono::steady_clock::now();
    bcSolver.Solve(puzzle, actualSollutionBc);
    end = std::chrono::steady_clock::now();
    cout << "Time BC: " << chrono::duration_cast<chrono::nanoseconds> (end - start).count() << "[ns]" << endl;

    // assertPuzzles(actualSollution, expectedSollution);
    return 0;
}

