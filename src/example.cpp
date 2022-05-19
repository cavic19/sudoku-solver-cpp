#include <iostream>
#include "Parser.h"
#include <string>
#include "CPSolver.h"
#include "Logging.h"
#include <chrono>
#include "BacktrackingSolver.h"

using namespace Sudoku;
using namespace std;
string easyPuzzle = "..3.2.6..9..3.5..1..18.64....81.29..7.......8..67.82....26.95..8..2.3..9..5.1.3..;483921657967345821251876493548132976729564138136798245372689514814253769695417382";
string hardPuzzle = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......;417369825632158947958724316825437169791586432346912758289643571573291684164875293";
string maybeHardPuzzle = "..............3.85..1.2.......5.7.....4...1...9.......5......73..2.1........4...9;..............3.85..1.2.......5.7.....4...1...9.......5......73..2.1........4...9";
string superHardPuzzle = "8..........36......7..9.2...5...7.......457.....1...3...1....68..85...1..9....4..;812753649943682175675491283154237896369845721287169534521974368438526917796318452";
int main()
{
    Parser parser(9, ';','.', -1);
    int puzzle[81];
    int expectedSollution[81];
    int actualSollution[81];
    parser.Parse(superHardPuzzle, puzzle, expectedSollution);   
    // CPSolver<3> solver;
    // chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    // solver.Solve(puzzle, actualSollution);
    // chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // cout << "Time CP: " << chrono::duration_cast<chrono::nanoseconds> (end - start).count() << "[ns]" << endl;

    int actualSollutionBc[81];
    BacktrackingSolver<3> bcSolver;
    chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    bcSolver.Solve(puzzle, actualSollutionBc);
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Time BC: " << chrono::duration_cast<chrono::nanoseconds> (end - start).count() << "[ns]" << endl;
    printPuzzle(actualSollutionBc, 9);
    // assertPuzzles(actualSollution, expectedSollution);
    return 0;
}

