#include <iostream>
#include "C:\Program Files (x86)\Microsoft SDKs\MPI\Include\mpi.h"
#include <string>
#include <queue>
#include <chrono>
#include "..\src\Parser.h"
#include "..\src\Logging.h"
#include "..\src\BacktrackingSolver.h"
#include "..\src\BaordGenerator.h"
#include "..\src\IndexedQueue.cpp"

const int BASE = 3;
const int WIDTH = BASE * BASE;
const int CELL_COUNT = WIDTH * WIDTH;

int puzzle[CELL_COUNT];
int actualSolution[CELL_COUNT];

void InitPuzzles(std::string puzzleLine, bool withSolution);
int main(int argc, char** argv)
{
    int nproc, iproc;
    InitPuzzles(
        "3.6.7...........518.........1.4.5...7.....6.....2......2.....4.....8.3.....5.....", 
        false);
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &iproc);
    auto start = std::chrono::steady_clock::now();
    Sudoku::Board<BASE> boardOrig(puzzle);
    Sudoku::IndexedQueue<Sudoku::Board<BASE>*, 100> queue;
    queue.Enqueue(&boardOrig);
    Sudoku::BoardGenerator::Generate(queue, nproc);

    Sudoku::BacktrackingSolver<BASE> solver(*queue[iproc]);
    if(solver.Solve())
    {
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        std::cout << "Process " << iproc << " found a solution in " << elapsed << "ms" << std::endl;
        // Sudoku::assertPuzzles(*queue.front(), actualSolution);
        Sudoku::printPuzzle(queue[iproc]);
    }
    else
    {
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        std::cout << "Process " << iproc << " failed after " << elapsed << "ms" << std::endl;
    }
  
    MPI_Finalize();
    return 0;
}


void InitPuzzles(std::string puzzleLine, bool withSolution = false)
{
    Sudoku::Parser p(WIDTH);
    if (withSolution)
    {

        p.Parse(puzzleLine, puzzle, actualSolution);
    }
    else
    {
        p.Parse(puzzleLine, puzzle);
    }
}
