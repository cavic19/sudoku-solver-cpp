#include <iostream>
#include "Parser.h"
#include <string>
#include "CPSolver.h"
#include "Logging.h"

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
    solver.Solve(puzzle, actualSollution);
    printPuzzle(actualSollution, 9);

    string errorMessage = "";  
    assertPuzzles(actualSollution, expectedSollution);
    return 0;
}

