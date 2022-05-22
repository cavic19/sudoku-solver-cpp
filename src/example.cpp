// #include <iostream>
// // #include "C:\Program Files (x86)\Microsoft SDKs\MPI\Include\mpi.h"
// #include "Parser.h"
// #include "Logging.h"
// #include "BacktrackingSolver.h"
// #include <string>
// #include <stack>
// #include <tuple>
// #include "DFSSolver.cpp"

// const int BASE = 3;
// const int WIDTH = BASE * BASE;
// const int CELL_COUNT = WIDTH * WIDTH;

// int puzzle[CELL_COUNT];
// int expectedSolution[CELL_COUNT];

// void InitPuzzles(std::string puzzleLine, bool withSolution);
// int main(int argc, char** argv)
// {
//     int nproc, iproc;
//     InitPuzzles(
//         "8..........36......7..9.2...5...7.......457.....1...3...1....68..85...1..9....4..;812753649943682175675491283154237896369845721287169534521974368438526917796318452", 
//         true);
//     int actualSolution[CELL_COUNT];

//     Sudoku::Board<BASE> b(puzzle);

//     // Sudoku::DFSSolver<3>::Solve(puzzle, actualSolution);
//     // Sudoku::printPuzzle(actualSolution, WIDTH);
//     // std::cout << std::endl;
//     // std::cout << std::endl;

//     // Sudoku::assertPuzzles(actualSolution, expectedSolution, WIDTH);


//     return 0;
// }


// void InitPuzzles(std::string puzzleLine, bool withSolution = false)
// {
//     Sudoku::Parser p(WIDTH);
//     if (withSolution)
//     {

//         p.Parse(puzzleLine, puzzle, expectedSolution);
//     }
//     else
//     {
//         p.Parse(puzzleLine, puzzle);
//     }
// }

// int createBoardType()
// {

// }

